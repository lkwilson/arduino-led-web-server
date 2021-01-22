#include <static_web_files.hpp>
#include <WiFiManager.h>
#include <FastLED.h>
#include <ESP8266WiFi.h>

// Constants
constexpr char ssid[] = "SSID_VALUE";
constexpr char password[] = "WIFI_PASSWD";
constexpr int port = 80;
constexpr int connection_timeout = 2000;
constexpr int max_value = 1023;
constexpr int red_output_pin = 4;
constexpr int green_output_pin = 14;
constexpr int blue_output_pin = 12;

// State
WiFiServer s_server(port);
int s_red;
int s_green;
int s_blue;

namespace Color {

// API
enum class Types {
  RED,
  GREEN,
  BLUE,
};

String convert_color(const Types color) {
  switch (color) {
    case Types::RED: return "red";
    case Types::GREEN: return "green";
    case Types::BLUE: return "blue";
  }
}

int& get_color_state(const Types color) {
  switch (color) {
    case Types::RED: return s_red;
    case Types::GREEN: return s_green;
    case Types::BLUE: return s_blue;
  }
}

int get_color_pin(const Types color) {
  switch (color) {
    case Types::RED: return red_output_pin;
    case Types::GREEN: return green_output_pin;
    case Types::BLUE: return blue_output_pin;
  }
}

// Assumes arguments are valid
void set_color(const Types color_type, const int value) {
  auto& color = get_color_state(color_type);
  if (color != value) {
    color = value;
    const auto pin = get_color_pin(color_type);
    analogWrite(pin, value);
  }
}

// Assumes arguments are valid
void set_colors(const int red_value, const int green_value, const int blue_value) {
  set_color(Types::RED, red_value);
  set_color(Types::GREEN, green_value);
  set_color(Types::BLUE, blue_value);
}

// HELPERS
void normalize_color_value(int& value) {
  if (value > max_value) {
    value = max_value;
  } else if (value < 0) {
    value = 0;
  }
}

String color_str() {
  return String(s_red) + ' ' + String(s_green) + ' ' + String(s_blue);
}

} // namespace Color

// SETUP
void setup_pins() {
  pinMode(red_output_pin, OUTPUT);
  pinMode(green_output_pin, OUTPUT);
  pinMode(blue_output_pin, OUTPUT);

  Color::set_colors(100, 100, 100);
}

void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

namespace Routing {

// REQUEST HANDLING
template<typename client_t>
String get_request(client_t&& client, const clock_t timeout) {
  String request = "";
  // Technically the request should tell us how long the message is, but this is
  // fine.
  while (client.connected() && !request.endsWith("\n\n")) {
    if (millis() > timeout) {
      Serial.println("Dropping client due to timeout");
      break;
    } else if (!client.available()) {
      continue;
    }

    char c = client.read();
    if (c == '\r') {
      continue;
    }
    request += c;
  }
  return request;
}

void minify(String& str) {
  str.trim();
  str.replace("  ", " ");
  while (-1 != str.indexOf("  ")) {
    str.replace("  ", " ");
  }
  str.replace("> <", "><");
}

String home_route() {
  String response = /* HTML_SED_HOOK */ R"HTML_VALUE(
  )HTML_VALUE";
  response.replace("RED_VALUE", String(s_red));
  response.replace("GREEN_VALUE", String(s_green));
  response.replace("BLUE_VALUE", String(s_blue));
  minify(response);
  return response;
}

template<typename client_t>
void respond(client_t&& client, const String& response) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
  client.println(response);
}

String handle_get(const String& request) {
  if (request.startsWith("/red")) {
    Serial.print("Getting red: ");
    Serial.println(s_red);
    return String(s_red);
  } else if (request.startsWith("/green")) {
    Serial.print("Getting green: ");
    Serial.println(s_green);
    return String(s_green);
  } else if (request.startsWith("/blue")) {
    Serial.print("Getting blue: ");
    Serial.println(s_blue);
    return String(s_blue);
  } else if (request.startsWith("/color")) {
    Serial.print("Getting colors: ");
    const auto ret = Color::color_str();
    Serial.println(ret);
    return ret;
  } else {
    return home_route();
  }
}

struct ParsedUrlInt {
  ParsedUrlInt(const String& url) {
    // is valid
    if (!url.startsWith("/") || url.length() == 1) {
      success = false;
      return;
    }
    // post: url starts with "/" and has length > 1 

    // get value
    const auto value_str = url.substring(1);
    value = value_str.toInt();
    success = value != 0 || isDigit(value_str[0]);
    if (!success) {
      return;
    }

    for (next_idx = 0; next_idx < value_str.length(); ++next_idx) {
      char c = value_str[next_idx];
      if (isDigit(c)) {
        continue;
      } else if (c == '/') {
        next_str = value_str.substring(next_idx);
        break;
      } else {
        next_idx = -1;
        break;
      }
    }
  }

  bool success;
  int value;
  int next_idx;
  String next_str;
};

String handle_post_color(const Color::Types color, const String& url) {
  ParsedUrlInt value(url);
  if (!value.success) {
    Serial.printf("Invalid value while setting %s\n", convert_color(color).c_str());
    return "";
  }

  auto& new_value = value.value;
  Color::normalize_color_value(new_value);
  Color::set_color(color, new_value);
  Serial.printf("Setting %s to %d\n", convert_color(color).c_str(), new_value);
  return String(new_value);
}

String handle_post_colors(const String& url) {
  ParsedUrlInt red_value(url);
  if (!red_value.success && red_value.next_idx != -1) {
    Serial.printf("Malformed colors request on red: %s\n", url.c_str());
    return "";
  }
  ParsedUrlInt green_value(red_value.next_str);
  if (!green_value.success && green_value.next_idx != -1) {
    Serial.printf("Malformed colors request on green: %s\n", url.c_str());
    return "";
  }
  ParsedUrlInt blue_value(green_value.next_str);
  if (!blue_value.success) {
    Serial.printf("Malformed colors request on blue: %s\n", url.c_str());
    return "";
  }

  auto& new_red = red_value.value;
  auto& new_green = green_value.value;
  auto& new_blue = blue_value.value;

  Color::normalize_color_value(new_red);
  Color::normalize_color_value(new_green);
  Color::normalize_color_value(new_blue);
  Serial.printf("Setting colors to: %d %d %d\n", new_red, new_green, new_blue);
  Color::set_colors(new_red, new_green, new_blue);
  return Color::color_str();
}

const String red_set_request = "/red";
const String green_set_request = "/green";
const String blue_set_request = "/blue";
const String color_set_request = "/color";
String handle_post(const String& request) {
  if (request.startsWith(red_set_request)) {
    return handle_post_color(Color::Types::RED, request.substring(red_set_request.length()));
  } else if (request.startsWith(green_set_request)) {
    return handle_post_color(Color::Types::GREEN, request.substring(green_set_request.length()));
  } else if (request.startsWith(blue_set_request)) {
    return handle_post_color(Color::Types::BLUE, request.substring(blue_set_request.length()));
  } else if (request.startsWith(color_set_request)) {
    return handle_post_colors(request.substring(color_set_request.length()));
  } else {
    Serial.println("Invalid post request");
    return "";
  }
}

const String get_prefix = "GET ";
const String post_prefix = "POST ";
String handle_request(const String& request) {
  if (request.startsWith(get_prefix)) {
    return handle_get(request.substring(get_prefix.length()));
  } else if (request.startsWith(post_prefix)) {
    return handle_post(request.substring(post_prefix.length()));
  } else {
    Serial.println("Unsupported http request type");
    return "";
  }
}

template<typename client_t>
void handle_client(client_t&& client, const clock_t timeout) {
  const auto& request = get_request(client, timeout);
  if (request.length() == 0) {
    Serial.println("Client didn't send anything");
    return;
  }
  const auto response = handle_request(request);
  respond(client, response);
}

} // namespace Routing

// HOOKS
void setup() {
  Serial.begin(115200);
  setup_pins();
  setup_wifi();
  s_server.begin();
}

void loop(){
  auto client = s_server.available();
  if (not client) {
    return;
  }

  const auto connection_time = millis();
  Serial.print("New client connected at time: ");
  Serial.println(connection_time);

  const auto timeout = connection_time + connection_timeout;
  Routing::handle_client(client, timeout);

  client.stop();

  Serial.println("Client disconnected.");
  Serial.println();
}
