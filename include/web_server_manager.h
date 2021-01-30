#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

struct WebServerManager {
  public: // ctors
    WebServerManager() : m_server(80) {}

  public: // api
    /**
     *  handler_t is a type that has a method with signature
     *    void add_handles(AsyncWebServer&);
     */
    template<typename ...handlers_t>
    void setup(handlers_t&&... handlers) {
      if (!LittleFS.begin()) {
        Serial.println("Unable to mount LittleFS directory");
      }
      m_server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
      m_server.onNotFound([this](AsyncWebServerRequest *request) { this->on_not_found(request); });

      add_handlers(std::forward<handlers_t>(handlers)...);

      m_server.begin();
    }

  private: // handlers
    void on_not_found(AsyncWebServerRequest *request) {
      Serial.println("Received not found request. Responding with 404.");
      request->send(404);
    }

  private: // helper methods
    template<typename handler_t, typename ...handlers_t>
    void add_handlers(handler_t&& handler, handlers_t&&... handlers) {
      add_handlers(std::forward<handler_t>(handler));
      add_handlers(std::forward<handlers_t>(handlers)...);
    }

    template<typename handler_t>
    void add_handlers(handler_t&& handler) {
      handler.add_handles(m_server);
    }

    void add_handlers() { /* no handler case */ }

  private: // members
    AsyncWebServer m_server;
};
