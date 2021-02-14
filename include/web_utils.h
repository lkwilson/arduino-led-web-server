#pragma once

#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>

namespace WebUtils {

template<typename msg_t>
void error(AsyncWebServerRequest* request, msg_t&& msg) {
  // TODO: Support error codes
  request->send(400, "text/plain", std::forward<msg_t>(msg));
}

const String missing_key_str = "Missing JSON key: ";
const String invalid_value_str = "Invalid value type for ";

template<typename value_t, typename json_t, typename json_key_t>
bool parse_json_value(AsyncWebServerRequest* request, value_t& value, json_t&& json, const json_key_t& key) {
  auto&& json_value = json[key];
  if (not json_value.template is<value_t>()) {
    WebUtils::error(request, WebUtils::invalid_value_str + key);
    return false;
  }

  value = json_value.template as<value_t>();
  return true;
}

// returns false if an error occurred
template<typename value_t, typename json_t, typename json_key_t>
bool load_value_if_any(AsyncWebServerRequest* request, value_t& value, json_t&& json, const json_key_t& key) {
  // ensure has key
  if (not json.containsKey(key)) {
    return true;
  }
  return parse_json_value(request, value, json, key);
}

// maybe return struct or by param to avoid allocating on the he
template<typename value_t, typename json_t, typename json_key_t>
bool load_value(AsyncWebServerRequest* request, value_t& value, json_t&& json, const json_key_t& key) {
  // ensure has key
  if (not json.containsKey(key)) {
    WebUtils::error(request, WebUtils::missing_key_str + key);
    return false;
  }
  return parse_json_value(request, value, json, key);
}

} // namespace WebUtils
