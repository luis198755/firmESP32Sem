void webServerTask(void * parameter) {
  setupServer();
  // Set up MQTT
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  client.setBufferSize(1024);

  //delay(500);
  //unsigned long currentMillis = 0;

  for(;;) {
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
    //dateTime.getCurrentDateTime(); // Print the current date and time

    //currentMillis = millis(); // Get the current time
    //dateTime.getCurrentDateTime(); // Print the current date and time

    if (millis() - previousMillis >= interval) { // If interval is exceeded
      previousMillis = millis(); // Save the current time
      
      dateTime.getCurrentDateTime(); // Print the current date and time
      dateTime.displayInfoGPS();

      //events.print();

      digitalWrite (exec.led_pin, !digitalRead (exec.led_pin));

      if ( counEvent0 == 10 ) { // Event every 10 s
        devices.sendStatus();
        counEvent0 = 0;
      }
      counEvent0++;

      // Serial.print("Ciclo: ");
      // Serial.println(scheduler.cycle);

    }

    gps_p();
    
    
    //vTaskDelay(1); // Delay for 1 tick period
    //delay(10); // Yield to the ESP32
  }
}