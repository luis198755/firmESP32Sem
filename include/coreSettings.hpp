#include "WebServerESP32.hpp"

/////////////// ================================== Se crea la instancia
WebServerESP32 webServer(80);

void webServerTask(void * parameter) {

  setupServer();
  /////////////// ================================== inicia modificacion
    // webServer.connectToWiFi("YOUR_SSID", "YOUR_PASSWORD"); // Connect to WiFi
    webServer.startServer(); // Start the web server

  /////////////// ================================== termina modificación
  // Set up MQTT
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  client.setBufferSize(1024);

  for(;;) {
    //scheduler.checkAndTriggerEvents();

    status = WiFi.status();
    if(status == WL_CONNECTED) {
      //Serial.println("WiFi Connected");
      if (!client.connected()) {
        reconnect();
        statusWifi = "On";
      }
      client.loop();

      /////////////// ================================== inicia modificacion (agregar la linea del handleClient)
      //webServer.handleClient(); // Handle client requests 
      /////////////// ================================== termina modificacion

      dateTime.setClock(); // Set date if RTC lost power

    } else {
        //Serial.println("WiFi Not Connected");
        statusWifi = "Off";
        wm.autoConnect(ap_nameap,ap_passwordap); // password protected ap
    }

    /////////////// ================================== inicia modificacion (agregar la linea del handleClient)
    webServer.handleClient(); // Handle client requests 
    /////////////// ================================== termina modificacion

    devices.getStatus();
    
    //vTaskDelay(1); // Delay for 1 tick period
    //delay(10); // Yield to the ESP32
  }
}