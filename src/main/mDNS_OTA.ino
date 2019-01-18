#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>                                      // Useful to access to ESP by hostname.local

void enableMDNSServices() {
    // Configure OTA Update
    ArduinoOTA.setPort(8266);
    ArduinoOTA.setHostname(host_name);
    ArduinoOTA.onStart([]() {
      Serial.println("Start");
    });
    ArduinoOTA.onEnd([]() {
      Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.begin();
    Serial.println("ArduinoOTA started");

    // Configure mDNS
    MDNS.addService("http", "tcp", port); // Announce the ESP as an HTTP service
    Serial.println("MDNS http service added. Hostname is set to " + String(host_name) + ".local:" + String(port));
}

