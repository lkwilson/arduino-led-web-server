#pragma once

#include <ESP8266WiFi.h>

struct WiFiManager {
    void setup() {
      Serial.println("Connecting to WiFi");
      configure();
      const auto results = WiFi.begin();
      if (results != WL_CONNECTED) {
        wait_for_connection();
      }
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
    }

    void wait_for_connection() {
      while (true) {
        const auto results = WiFi.waitForConnectResult(10000UL);
        switch (results) {
          case WL_CONNECTED: {
            // assigned when connected to a WiFi network;
            Serial.println("(WL_CONNECTED) Connection successful");
            return;
          }

          case WL_IDLE_STATUS: {
            // it is a temporary status assigned when WiFi.begin() is called and
            // remains active until the number of attempts expires (resulting in
            // WL_CONNECT_FAILED) or a connection is established (resulting in
            // WL_CONNECTED);
            Serial.println("(WL_IDLE_STATUS) Still attempting to connect");
            break;
          }

          case WL_NO_SSID_AVAIL: {
            // assigned when no SSID are available;
            Serial.println("(WL_NO_SSID_AVAIL) No SSID available");
            break;
          }

          case WL_SCAN_COMPLETED: {
            // assigned when the scan networks is completed;
            Serial.println("(WL_SCAN_COMPLETED) Finished Scanning");
            break;
          }

          case WL_CONNECT_FAILED: {
            // assigned when the connection fails for all the attempts;
            Serial.println("(WL_CONNECT_FAILED) Failed to connect to WiFi");
            WiFi.begin();
            break;
          }

          case WL_CONNECTION_LOST: {
            // assigned when the connection is lost;
            Serial.println("(WL_CONNECTION_LOST) Connection was lost");
            reconnect();
            break;
          }

          case WL_DISCONNECTED: {
            // assigned when disconnected from a network
            Serial.println("(WL_DISCONNECTED) Disconnected from a network");
            reconnect();
            break;
          }

          case -1: { // Timeout
            Serial.println("(TIMEOUT) Connecting to WiFi timed out.");
            break;
          }

          default:
          {
            Serial.println("Invalid connection status received");
            break;
          }
        }
      }
    }

  private:
    void configure() {
      WiFi.setAutoConnect(true);
      WiFi.setAutoReconnect(true);
    }

    void reconnect() {
      Serial.println("Reconnecting to wifi");
      WiFi.reconnect();
    }
};
