void webServerTask(void * parameter) {
  setupServer();
  // Set up MQTT
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  client.setBufferSize(1024);

  for(;;) {
    unsigned long currentMillis = millis(); // Get the current time
    
    status = WiFi.status();
    if(status == WL_CONNECTED) {
      //Serial.println("WiFi Connected");
      if (!client.connected()) {
      reconnect();
      statusWifi = "On";
      }
      client.loop();
      server.handleClient(); // Handle client requests

      dateTime.setClock(); // Set date if RTC lost power

    } else {
      //Serial.println("WiFi Not Connected");
      statusWifi = "Off";
      wm.autoConnect(ap_nameap,ap_passwordap); // password protected ap
      
    }

    devices.getStatus();

    if (currentMillis - previousMillis >= interval) { // If interval is exceeded
      previousMillis = currentMillis; // Save the current time
      
      dateTime.printCurrentDateTime(); // Print the current date and time
      dateTime.displayInfoGPS();

      digitalWrite (exec.led_pin, !digitalRead (exec.led_pin));

      if ( counEvent0 == 10 ) { // Event every 10 s
        devices.sendStatus();
        counEvent0 = 0;
      }
      counEvent0++;

    }

    gps_p();
    
    
    //vTaskDelay(1); // Delay for 1 tick period
    //delay(10); // Yield to the ESP32
  }
}