void webServerTask(void * parameter) {
  // dateTime.getCurrentDateTime(); // Print the current date and time

  // // Scheduler Set
  // scheduler.scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 5, 0, 0), 0, 0); // (DateTime, Cycle, Sincr)
  // scheduler.scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 10, 0, 0), 1, 10); // (DateTime, Cycle, Sincr)
  // scheduler.scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 10, 4, 0), 2, 30); // (DateTime, Cycle, Sincr)
  // scheduler.scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 13, 16, 0), 1, 10); // (DateTime, Cycle, Sincr)
  // scheduler.scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 13, 22, 0), 1, 0); // (DateTime, Cycle, Sincr)
  // scheduler.scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 13, 28, 0), 1, 10); // (DateTime, Cycle, Sincr)
  // scheduler.scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 13, 32, 0), 1, 0); // (DateTime, Cycle, Sincr)
  // scheduler.scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 13, 40, 0), 1, 0); // (DateTime, Cycle, Sincr)
  // delay(1000);
  

  setupServer();
  // Set up MQTT
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  client.setBufferSize(1024);

  //delay(500);
  //unsigned long currentMillis = 0;

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
    //gps_p();
    
    //vTaskDelay(1); // Delay for 1 tick period
    //delay(10); // Yield to the ESP32
  }
}