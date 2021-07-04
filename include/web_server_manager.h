#include <ESPAsyncWebServer.h>
#ifdef ESP32
#include <LITTLEFS.h>
#define LittleFS LITTLEFS
#else
#include <LittleFS.h>
#endif

#include <ESP32SSDP.h>

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

      add_handlers(std::forward<handlers_t>(handlers)...);

      config_ssdp();
      m_server.on("/description.xml", HTTP_GET, [this](AsyncWebServerRequest* request) {
        request->send(200, "text/plain", SSDP.schema());
      });

      m_server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
      m_server.onNotFound([this](AsyncWebServerRequest *request) { this->on_not_found(request); });

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

    void config_ssdp() const
    {
      //set schema xml url, nees to match http handler
      //"ssdp/schema.xml" if not set
      SSDP.setSchemaURL("description.xml");
      //set port
      //80 if not set
      SSDP.setHTTPPort(80);
      //set device name
      //Null string if not set
      SSDP.setName("qrled");
      //set Serial Number
      //Null string if not set
      SSDP.setSerialNumber("001788102201");
      //set device url
      //Null string if not set
      SSDP.setURL("index.html");
      //set model name
      //Null string if not set
      SSDP.setModelName("Qualtiy Robot LED System");
      //set model description
      //Null string if not set
      SSDP.setModelDescription("This device can be controled by WiFi");
      //set model number
      //Null string if not set
      SSDP.setModelNumber("929000226503");
      //set model url
      //Null string if not set
      SSDP.setModelURL("http://github.com/quality-robot");
      //set model manufacturer name
      //Null string if not set
      SSDP.setManufacturer("Quality Robot");
      //set model manufacturer url
      //Null string if not set
      SSDP.setManufacturerURL("http://github.com/quality-robot");
      //set device type
      //"urn:schemas-upnp-org:device:Basic:1" if not set
      SSDP.setDeviceType("upnp:rootdevice"); //to appear as root device
      //set server name
      //"Arduino/1.0" if not set
      SSDP.setServerName("SSDPServer/1.0");
      //set UUID, you can use https://www.uuidgenerator.net/
      //use 38323636-4558-4dda-9188-cda0e6 + 4 last bytes of mac address if not set
      //use SSDP.setUUID("daa26fa3-d2d4-4072-bc7a-a1b88ab4234a", false); for full UUID
      SSDP.setUUID("daa26fa3-d2d4-4072-bc7a");
      //Set icons list, NB: optional, this is ignored under windows
      SSDP.setIcons(
          "<icon>"
          "<mimetype>image/png</mimetype>"
          "<height>48</height>"
          "<width>48</width>"
          "<depth>24</depth>"
          "<url>icon48.png</url>"
          "</icon>");
      //Set service list, NB: optional for simple device
      //SSDP.setServices(
          //"<service>"
          //"<serviceType>urn:schemas-upnp-org:service:SwitchPower:1</serviceType>"
          //"<serviceId>urn:upnp-org:serviceId:SwitchPower:1</serviceId>"
          //"<SCPDURL>/SwitchPower1.xml</SCPDURL>"
          //"<controlURL>/SwitchPower/Control</controlURL>"
          //"<eventSubURL>/SwitchPower/Event</eventSubURL>"
          //"</service>");

      Serial.println("Starting SSDP...");
      SSDP.begin();
    }
  private: // members
    AsyncWebServer m_server;
};
