#include <ESPAsyncWebServer.h>

struct WebServerManager {
  public: // ctors
    WebServerManager() : m_server(80) {}

  public: // api
    void setup() {
      m_server.begin();
      m_server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    }

  private: // members
    AsyncWebServer m_server;
};
