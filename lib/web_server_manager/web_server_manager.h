#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

struct WebServerManager {
  public: // ctors
    WebServerManager() : m_server(80) {}

  public: // api
    void setup() {
      if (!LittleFS.begin()) {
        Serial.println("Unable to mount LittleFS directory");
      }
      m_server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
      m_server.onNotFound([this](AsyncWebServerRequest *request){ this->on_not_found(request); });

      m_server.begin();
    }

  private: // handlers
    void on_not_found(AsyncWebServerRequest *request) {
      Serial.println("Received not found request. Responding with 404.");
      request->send(404);
    }

  private: // members
    AsyncWebServer m_server;
};
