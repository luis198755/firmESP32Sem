///////////////////////*Classes*/////////////////////////////////
class dateTimeMan {
public:
    void setTimeFromNTP() {
      timeClient.update();
      DateTime now = DateTime(timeClient.getEpochTime());
      rtc.adjust(now);
      Serial.println("Time set from NTP server");
    }
    void setClock () {
      if (rtc.lostPower()) {
      Serial.println("RTC lost power, lets set the time!");
      // following line sets the RTC to the date & time this sketch was compiled
      // Set the RTC to the date & time this sketch was compiled
      //rtc.adjust(DateTime(__DATE__, __TIME__));
      //rtc.adjust(DateTime(year(), month(), day(), hour(), minute(), second()));
      // This line sets the RTC with an explicit date & time, for example to set
      // January 21, 2014 at 3am you would call:
      //rtc.adjust(DateTime(2023, 2, 14, 9, 37, 0));

      // Initialize the NTP client
      timeClient.begin();
      // Update the time
      setTimeFromNTP();
      }
    }
    void printCurrentDateTime() {

        DateTime now = rtc.now();
        currentTime = now.unixtime();

        rtcHour = now.hour();
        rtcMinute = now.minute();
        rtcSecond = now.second();

        if (timeStatus()!= timeNotSet) {
          gpsSecond = second();
          gpsDay = day();
          gpsMonth = month();
          gpsYear = year();
          gpsHour = hour();
          gpsMinute = minute();
        }

        /*
        char buf[20];
        sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
        Serial.println(buf);
        */
    }

    // Función que muestra hora y fecha en OLED
    void displayInfoGPS() {
        
        oled.clearDisplay();			// limpia pantalla
        oled.setTextColor(WHITE);		// establece color al unico disponible (pantalla monocromo)
        oled.setCursor(0, 0);			// ubica cursor en inicio de coordenadas 0,0
        oled.setTextSize(1);			// establece tamano de texto en 1
        oled.print("M:"); 	// escribe en pantalla el texto
        oled.print(estado);
        oled.setCursor(80, 0);			// ubica cursor en inicio de coordenadas 0,0
        oled.print("Wifi:"); 	// escribe en pantalla el texto
        oled.print(statusWifi);
        
        oled.setCursor (0, 15);
        oled.print(gpsDay);
        oled.print("/");
        oled.print(gpsMonth);
        oled.print("/");
        oled.print(gpsYear); 
        oled.setCursor (0, 25);
        oled.print("GPS:");
        oled.print(gpsHour);
        oled.print(":");   
        oled.print(gpsMinute);
        oled.print(":"); 
        oled.print(gpsSecond);  
          
        oled.setCursor (0, 35);
        oled.print("RTC:");
        oled.print(rtcHour);
        oled.print(":");   
        oled.print(rtcMinute);
        oled.print(":"); 
        oled.print(rtcSecond);  
        //oled.setTextSize(3);			// establece tamano de texto en 2
        oled.display();			// muestra en pantalla todo lo establecido anteriormente
        //readRTC();
      }
};

dateTimeMan dateTime;

class devicesEsp32 {
  public:
    void sendData(String data) {
      if (WiFi.status() == WL_CONNECTED) {
        if (client.publish(topic, data.c_str())) {
        //Serial.println("Publish ok");
        //Serial.println("Core #"+String(xPortGetCoreID()));
        }
      }
      else {
          //Serial.println("Publish failed");
          statusWifi = "Off";
      }
      
    }

    void getStatus () {
      ip = WiFi.localIP().toString();
      rssi = WiFi.RSSI();
      txPower = WiFi.getTxPower();
      temperatureRTC = rtc.getTemperature();
    }

    void sendStatus () {

    // Populate the document
      doc["id"] = id;

      // Nested "RTC" object
      JsonObject rtc = doc.createNestedObject("RTC");
      rtc["timestamp"] = currentTime;
      rtc["temperature"] = temperatureRTC;

      // Nested "GPS" object
      JsonObject gps = doc.createNestedObject("GPS");
      gps["latitude"] = latitude;
      gps["logitude"] = longitude;
      gps["altitude"] = altitude;
      gps["satellites"] = satellites;

      // Nested "Ctrl" object
      JsonObject ctrl = doc.createNestedObject("Ctrl");
      ctrl["estado"] = estado;
      ctrl["resetWifi"] = stateReset;

      // Prog info
      JsonObject escenarios = ctrl.createNestedObject("escenarios");
      JsonArray escenarios1 = escenarios.createNestedArray("1");
      for(int i = 0; i < sizeEscn; i++) {
        escenarios1.add(firstColumn[i]);
      }

      JsonObject eventos = ctrl.createNestedObject("eventos");
      JsonArray eventos1 = eventos.createNestedArray("1");
      for(int i = 0; i < sizeEvent; i++) {
        eventos1.add(eventArray1[i]);
      }
      JsonArray eventos2 = eventos.createNestedArray("2");
      for(int i = 0; i < sizeEvent; i++) {
        eventos2.add(eventArray2[i]);
      }
      JsonArray eventos3 = eventos.createNestedArray("3");
      for(int i = 0; i < sizeEvent; i++) {
        eventos3.add(eventArray3[i]);
      }
      JsonArray eventos4 = eventos.createNestedArray("4");
      for(int i = 0; i < sizeEvent; i++) {
        eventos4.add(eventArray4[i]);
      }
      JsonArray eventos5 = eventos.createNestedArray("5");
      for(int i = 0; i < sizeEvent; i++) {
        eventos5.add(eventArray5[i]);
      }
      JsonArray eventos6 = eventos.createNestedArray("6");
      for(int i = 0; i < sizeEvent; i++) {
        eventos6.add(eventArray6[i]);
      }
      JsonArray eventos7 = eventos.createNestedArray("7");
      for(int i = 0; i < sizeEvent; i++) {
        eventos7.add(eventArray7[i]);
      }
      JsonArray eventos8 = eventos.createNestedArray("8");
      for(int i = 0; i < sizeEvent; i++) {
        eventos8.add(eventArray8[i]);
      }


      JsonObject ciclos = ctrl.createNestedObject("ciclos");
      JsonArray ciclos1 = ciclos.createNestedArray("1");
      for(int i = 0; i < sizeCycle; i++) {
        ciclos1.add(matrix[i][0]);
      }
      JsonArray ciclos2 = ciclos.createNestedArray("2");
      for(int i = 0; i < sizeCycle; i++) {
        ciclos2.add(matrix[i][1]);
      }
      JsonArray ciclos3 = ciclos.createNestedArray("3");
      for(int i = 0; i < sizeCycle; i++) {
        ciclos3.add(matrix[i][2]);
      }
      JsonArray ciclos4 = ciclos.createNestedArray("4");
      for(int i = 0; i < sizeCycle; i++) {
        ciclos4.add(matrix[i][3]);
      }
      JsonArray ciclos5 = ciclos.createNestedArray("5");
      for(int i = 0; i < sizeCycle; i++) {
        ciclos5.add(matrix[i][4]);
      }
      JsonArray ciclos6 = ciclos.createNestedArray("6");
      for(int i = 0; i < sizeCycle; i++) {
        ciclos6.add(matrix[i][5]);
      }
      JsonArray ciclos7 = ciclos.createNestedArray("7");
      for(int i = 0; i < sizeCycle; i++) {
        ciclos7.add(matrix[i][6]);
      }
      JsonArray ciclos8 = ciclos.createNestedArray("8");
      for(int i = 0; i < sizeCycle; i++) {
        ciclos8.add(matrix[i][7]);
      }

      JsonObject sincronias = ctrl.createNestedObject("sincronias");
      JsonArray sincronias1 = sincronias.createNestedArray("1");
      for(int i = 0; i < sizeSincro; i++) {
        sincronias1.add(sincroArray1[i]);
      }
      // Nested "Wifi" object
      JsonObject wifi = doc.createNestedObject("Wifi");
      wifi["rssi"] = rssi;
      wifi["txPower"] = txPower;
      wifi["ip"] = ip;

      
      serializeJson(doc, output);
      sendData(output);

      /*
      Serial.print("ID: ");
      Serial.println(doc["id"].as<String>());
      */
    }

};

devicesEsp32 devices;

class ReadConf {
  private:

    // Assuming max 8 rows for simplicity in the example, adjust as necessary
    unsigned long firstColumnValues[8]; // Escenarios
    unsigned int secondToNinthColumns[8][8]; // Ciclos

    unsigned long firstColumnValuesProv[40]; // Escenarios
    unsigned int secondToNinthColumnsProv[40][8]; // Ciclos

    unsigned int tenthColumnValues[8]; // Sincronías
    unsigned int eleventhTwelfthColumns[8][2]; // Hora, minutos
    int rowIndex = 0; // Track the current row index for array storage
  
  public:

    void readSCV() {
      // Open the file for reading
      myFile = SD.open("/config/progProv.conf", FILE_READ);

      if (myFile) {
        Serial.println("Reading from file...");
        // Read from the file until there's nothing else in it:
        while (myFile.available()) {
          String csvLine = myFile.readStringUntil('\n');
          Serial.println(csvLine);
          parseCSVprov(csvLine);
        }
        // Close the file
        myFile.close();
      } else {
        // If the file didn't open, print an error
        Serial.println("Error opening data.csv for reading");
      }
    }

    void parseCSV(String csvLine) {
      int maxColumns = 12; // Max number of columns in the CSV
      int columnIndex = 0; // To track the current column index within the row

      // Split the CSV line into tokens
      int fromIndex = 0;
      int toIndex = 0;
      for (int i = 0; i < maxColumns; i++) {
        toIndex = csvLine.indexOf(',', fromIndex);
        if (toIndex == -1) toIndex = csvLine.length(); // Last value

        unsigned long value = strtoul(csvLine.substring(fromIndex, toIndex).c_str(), NULL, 10);

        if (i == 0) {
          // First column, store in unsigned long array
          firstColumnValues[rowIndex] = value;
        } else if (i >= 1 && i <= 8) {
          // Columns 2 to 9, store in 8x8 array
          secondToNinthColumns[rowIndex][i - 1] = (unsigned int)value;
        } else if (i == 9) {
          // Tenth column, store in unsigned int array
          tenthColumnValues[rowIndex] = (unsigned int)value;
        } else if (i >= 10 && i <= 11) {
          // Eleventh and Twelfth columns, store in 8x2 array
          eleventhTwelfthColumns[rowIndex][i - 10] = (unsigned int)value;
        }

        fromIndex = toIndex + 1;
      }

      rowIndex++; // Move to the next row for the next call
    }

    // Add additional functions or modify existing ones as needed
    void printArrays() {
      Serial.println("Escenarios:");
      for (int i = 0; i < rowIndex; i++) {
        Serial.println(firstColumnValues[i]);
      }
      
      Serial.println("Ciclos:");
      for (int i = 0; i < rowIndex; i++) {
        for (int j = 0; j < 8; j++) {
          Serial.print(secondToNinthColumns[i][j]);
          if (j < 7) Serial.print(", ");
        }
        Serial.println();
      }
      
      Serial.println("Sincronías:");
      for (int i = 0; i < rowIndex; i++) {
        Serial.println(tenthColumnValues[i]);
      }
      
      Serial.println("Hora,Minuto:");
      for (int i = 0; i < rowIndex; i++) {
        for (int j = 0; j < 2; j++) {
          Serial.print(eleventhTwelfthColumns[i][j]);
          if (j < 1) Serial.print(", ");
        }
        Serial.println();
      }
    }

    void parseCSVprov(String csvLine) {
      int maxColumns = 9; // Max number of columns in the CSV
      int columnIndex = 0; // To track the current column index within the row

      // Split the CSV line into tokens
      int fromIndex = 0;
      int toIndex = 0;
      for (int i = 0; i < maxColumns; i++) {
        toIndex = csvLine.indexOf(',', fromIndex);
        if (toIndex == -1) toIndex = csvLine.length(); // Last value

        unsigned long value = strtoul(csvLine.substring(fromIndex, toIndex).c_str(), NULL, 10);

        if (i == 0) {
          // First column, store in unsigned long array
          firstColumnValuesProv[rowIndex] = value;
        } else if (i >= 1 && i <= 8) {
          // Columns 2 to 9, store in 8x8 array
          secondToNinthColumnsProv[rowIndex][i - 1] = (unsigned int)value;
        }

        fromIndex = toIndex + 1;
      }
      rowIndex++; // Move to the next row for the next call
    }

    // Add additional functions or modify existing ones as needed
    void printArraysProv() {
      Serial.println("Escenarios:");
      for (int i = 0; i < rowIndex; i++) {
        Serial.println(firstColumnValuesProv[i]);
      }
      
      Serial.println("Ciclos:");
      for (int i = 0; i < rowIndex; i++) {
        for (int j = 0; j < 8; j++) {
          Serial.print(secondToNinthColumnsProv[i][j]);
          if (j < 7) Serial.print(", ");
        }
        Serial.println();
      }
    }

};
ReadConf readconf;