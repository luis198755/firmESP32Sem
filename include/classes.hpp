///////////////////////*Classes*/////////////////////////////////

class oledTL {
  public:
    // Función de escritura de OLED
    void displayInfo(String modo) {
      /////////////////////OLED////////////////////////////
        oled.clearDisplay();			// limpia pantalla
        oled.setTextColor(WHITE);		// establece color al unico disponible (pantalla monocromo)
        oled.setCursor(0, 0);			// ubica cursor en inicio de coordenadas 0,0
        oled.setTextSize(1);			// establece tamano de texto en 1
        oled.print(modo); 	// escribe en pantalla el texto
        oled.display();			// muestra en pantalla todo lo establecido anteriormente
    }

    // Función que muestra mensaje en oled
    void showOLED(unsigned long mensaje) {
      oled.clearDisplay();			// limpia pantalla
      oled.setTextColor(WHITE);		// establece color al unico disponible (pantalla monocromo)
      oled.setCursor(0, 0);			// ubica cursor en inicio de coordenadas 0,0
      oled.setTextSize(1);			// establece tamano de texto en 1
      //oled.print("Modo: "); 	// escribe en pantalla el texto
      oled.print(mensaje);

      oled.display();			// muestra en pantalla todo lo establecido anteriormente
    }
};
oledTL oledtl;

class dateTimeMan {
public:
    DateTime now;

    void setTimeFromNTP() {
      timeClient.update();
      DateTime now = DateTime(timeClient.getEpochTime());
      rtc.adjust(now);
      Serial.println("Time set from NTP server");
      oledtl.displayInfo("Time set from NTP server");
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
        delay(500);
        // Update the time
        setTimeFromNTP();
        delay(1500);
      }
    }
    void getCurrentDateTime() {

        now = rtc.now();
        currentTime = now.unixtime();

        rtcDay = now.day();
        rtcMonth = now.month(); 
        rtcYear = now.year();
        rtcHour = now.hour();
        rtcMinute = now.minute();
        rtcSecond = now.second();
        
        //  char buf[20];
        //  sprintf(buf, "%02d-%02d-%04d %02d:%02d:%02d", rtcDay, rtcMonth, rtcYear, rtcHour, rtcMinute, rtcSecond);
        //  Serial.println(buf);
        
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
          
        oled.setCursor (0, 12);
        oled.print(rtcDay);
        oled.print("/");
        oled.print(rtcMonth);
        oled.print("/");
        oled.print(rtcYear);   
        oled.setCursor (70, 12);
        //oled.print("RTC:");
        oled.print(rtcHour);
        oled.print(":");   
        oled.print(rtcMinute);
        oled.print(":"); 
        oled.print(rtcSecond);  

        oled.setCursor (0, 22);
        oled.print(gpsDay);
        oled.print("/");
        oled.print(gpsMonth);
        oled.print("/");
        oled.print(gpsYear); 
        oled.setCursor (70, 22);
        //oled.print("GPS:");
        oled.print(gpsHour);
        oled.print(":");   
        oled.print(gpsMinute);
        oled.print(":"); 
        oled.print(gpsSecond);  

        oled.setCursor (0, 35);
        oled.print("Evento: ");
        oled.print(EventGen);

        oled.setCursor (0, 45);
        oled.print("Ciclo:  ");
        oled.print(CycleGen);

        oled.setCursor (0, 55);
        oled.print("Sincr.: ");
        oled.print(SyncGen);
        
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
      for(int i = 0; i < 4; i++) {
        escenarios1.add(firstColumn[i]);
      }

      // Ciclos
      JsonObject ciclos = ctrl.createNestedObject("ciclos");
      for (int j = 1; j <= 8; j++) {
        JsonArray ciclo = ciclos.createNestedArray(String(j));
        for (int i = 0; i < 8; i++) {
          ciclo.add(cycleArrayJson[i][j-1]);
        }
      }
 
      // Eventos
      JsonObject eventos = ctrl.createNestedObject("eventos");
      for (int j = 1; j <= 8; j++) {
          JsonArray evento = eventos.createNestedArray(String(j));
          for (int i = 0; i < 4; i++) {
              evento.add(eventArrayJson[i][j - 1]);
          }
      }

      // JsonObject sincronias = ctrl.createNestedObject("sincronias");
      // JsonArray sincronias1 = sincronias.createNestedArray("1");
      // for(int i = 0; i < sizeSincro; i++) {
      //   sincronias1.add(sincroArray1[i]);
      // }

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
  //private:
  //  int rowIndex = 0; // Track the current row index for array storage
  
  public:
    int rowIndex = 0; // Track the current row index for array storage
    // Assuming max 8 rows for simplicity in the example, adjust as necessary
    unsigned long firstColumnValues[8]; // Escenarios
    unsigned int secondToNinthColumns[8][8]; // Ciclos

    unsigned long firstColumnValuesProv[40]; // Escenarios
    unsigned int secondToNinthColumnsProv[40][8]; // Ciclos

    unsigned int tenthColumnValues[8]; // Sincronías
    unsigned int eleventhTwelfthColumns[8][2]; // Hora, minutos

    void readConf() {
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
          Serial.print(cycleArrayJson[i][j]);
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
          //prog00[rowIndex] = value;
        } else if (i >= 1 && i <= 8) {
          // Columns 2 to 9, store in 8x8 array
          cycleArrayJson[rowIndex][i - 1] = (unsigned int)value;
        }

        fromIndex = toIndex + 1;
      }
      rowIndex++; // Move to the next row for the next call
    }

    // Add additional functions or modify existing ones as needed
    void printArraysProv() {
      Serial.println("Escenarios:");
      for (int i = 0; i < rowIndex; i++) {
        Serial.println(progArrayJson[i]);
      }
      
      Serial.println("Ciclos:");
      for (int i = 0; i < rowIndex; i++) {
        for (int j = 0; j < 8; j++) {
          Serial.print(cycleArrayJson[i][j]);
          if (j < 7) Serial.print(", ");
        }
        Serial.println();
      }
    }

};
ReadConf readconf;

class RealTimeExec {
	private:
  		int pinData;
      int pinLatch;
      int pinClock;
      int pinOE;
  		
      void ledWrite(char Reg4, char Reg3, char Reg2, char Reg1){
           shiftOut(pinData, pinClock, LSBFIRST, Reg4);
           shiftOut(pinData, pinClock, LSBFIRST, Reg3);
           shiftOut(pinData, pinClock, LSBFIRST, Reg2);
           shiftOut(pinData, pinClock, LSBFIRST, Reg1);
           digitalWrite(pinLatch, HIGH);
           digitalWrite(pinLatch, LOW);
      }
  			
  		void interfaceProg(unsigned long var32Bits) {
          unsigned char var1 = (var32Bits & 0xFF) ^ 0xFF;
          unsigned char var2 = ((var32Bits >> 8) & 0xFF) ^ 0xFF;
          unsigned char var3 = ((var32Bits >> 16) & 0xFF) ^ 0xFF;
          unsigned char var4 = ((var32Bits >> 24) & 0xFF) ^ 0xFF;

      	  ledWrite(var1,var2,var3,var4);
		}
  
  	public:
  		unsigned long previousTime = 0;
  		int indice = 0;
      int led_pin = 13; // Embbeded Pin
      //int ciclo = 0;
  
  		RealTimeExec (int InpinData, int InpinLatch, int InpinClock, int InpinOE) {
        pinData = InpinData;
        pinLatch = InpinLatch;
        pinClock = InpinClock;
        pinOE = InpinOE;

        /*
        pinData = 12;
        pinLatch = 33;
        pinClock = 15;
        pinOE = 27;
        */
        unsigned long previousTime = 0;
  		  int indice = 0;
  		}

      void initReg() {
        pinMode(pinData, OUTPUT);
        pinMode(pinLatch, OUTPUT);
        pinMode(pinClock, OUTPUT);
        pinMode(pinOE, OUTPUT);
        pinMode (led_pin, OUTPUT); // Set the LED pin as output

        ////////////*Desactivar Registros*////////////////////////
        digitalWrite(pinOE, HIGH);
        ////////////*Activar Registros*////////////////////////
        digitalWrite(pinOE, LOW);
        // Apagado de todas las fases
        ledWrite(0xff,0xff,0xff,0xff);
        //interfaceProg(EscOff);
      }
  		
      void tiempoReal(unsigned int* time, unsigned long* prog, int longitud, unsigned int ciclo){
        //Revisión de tiempo cumplido
        if ( (millis() - previousTime >= (*(time + indice * (8) + ciclo))) ){//  *(time + indice)) ){ 
          //previousTime = millis();

          if (triggerEventFlag == true && indice == 0) {
            //Serial.println("Triggger Condition");
            indice = indice;
            //interfaceProg(*(prog + indice + 1));
          }
          else {
            indice++;
          }
          if (triggerEventFlag == true && rtcSecond == SyncGen) {
              triggerEventFlag = false;
              // Serial.println("EventFlag = ");
              // Serial.println(triggerEventFlag);
          }
          //previousTime = millis();
          // Si el índice llega al final del arreglo, reiniciarlo a cero
          if (indice >= longitud) {
              indice = 0;
              previousTime = 0;
              //previousTime = millis();
              //Serial.println("Synchronizing Sem");
          }
          else {
            if (triggerEventFlag == true && indice == 0) {
              interfaceProg(*(prog + indice + 1));
            }
            else {
              // Ejecución de la Programación
              interfaceProg(*(prog + indice));
            }
          }

          // if ( ((rtcMinute & 1) == 0) && (rtcSecond == 0 + SyncGen)) {
          //   Serial.println("Synchronizing Sem");
          //   previousTime = 0;
          //   indice = 0;
          // }

          previousTime = millis();
        }
      }

      void tiempoRealDestello(unsigned int* time, unsigned long* prog, int longitud){
        //Revisión de tiempo cumplido
        if ( (millis() - previousTime >= *(time + indice)) ){ //  *(time + indice)) ){ 
          previousTime = millis();

          // Incrementar el índice en uno
          indice++;

          // Si el índice llega al final del arreglo, reiniciarlo a cero
          if (indice >= longitud) {
              indice = 0;              
          }
          else {
              // Ejecución de la Programación
              interfaceProg(*(prog + indice));
          }

          if ( ((rtcMinute & 1) == 0) && (rtcSecond == 0 + SyncGen)) {
            Serial.println("Blink to Work Triggered");
            modo++;
            previousTime = millis();//previousTime = 0;
            indice = 0;
          }
          /*Serial.print("Indice: ");
          Serial.println(indice);*/
        }
      }

      unsigned long long millisESP32 () {
        return (unsigned long long) (esp_timer_get_time () / 1000ULL);
      }
}; 
RealTimeExec exec(12,33,15,27); // (InpinData, InpinLatch, InpinClock, InpinOE); Register control pins

struct Event {
    DateTime eventTime;
    bool triggered;
    unsigned int cycle;
    unsigned int synchrony;
    
    Event(const DateTime& dt, unsigned int cycle, unsigned int synchrony) : eventTime(dt), cycle(cycle), synchrony(synchrony), triggered(false) {

    }
};
class EventScheduler {
public:
    Event* events[8]; // Array to hold up to 8 events
    int eventCount = 0;
    unsigned int cycle = 0;

    void scheduleEvent(const DateTime& dt, unsigned int cycle, unsigned int synchrony) {
        if (eventCount < 8) {
            events[eventCount] = new Event(dt, cycle, synchrony);

            // Serial.print("Event : ");
            // Serial.print(eventCount);
            // Serial.print(" - ");
            // Serial.print("triggered : ");
            // Serial.print(events[eventCount]->triggered);
            // Serial.print(" - ");
            // Serial.print(events[eventCount]->eventTime.day());
            // Serial.print("/");
            // Serial.print(events[eventCount]->eventTime.month());
            // Serial.print("/");
            // Serial.print(events[eventCount]->eventTime.year());
            // Serial.print(" - ");
            // Serial.print(events[eventCount]->eventTime.hour());
            // Serial.print(":");
            // Serial.print(events[eventCount]->eventTime.minute());
            // Serial.print(":");
            // Serial.print(events[eventCount]->eventTime.second());
            // Serial.print(" - ");
            // Serial.print("ciclo: ");
            // Serial.print(events[eventCount]->cycle);
            // Serial.print(" - ");
            // Serial.print("sincronia: ");
            // Serial.println(events[eventCount]->synchrony);

            eventCount++;
        }
    }

    /*
    unsigned int eventArrayJson_[4][8] = {
                                        {5, 12, 17, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 1, 0, 0, 0, 0},
                                        {0, 1, 2, 1, 0, 0, 0, 0},
                                        {0, 10, 20, 0, 0, 0, 0, 0}
};
    */

    void checkAndTriggerEvents() {
        //DateTime now = rtc.now();
        if (rtcHour == 0 && rtcMinute == 0 && rtcSecond == 0 && flagDayChange == 0) {
            flagDayChange = 1;
            EventScheduler::eventCount = 0;
            setScheduler();

            // for (int i = 0; i < eventCount; i++) {
            //   // Serial.print("Trigger event: ");
            //   // Serial.print(i);
            //   // Serial.print(" - ");
            //   // Serial.println(events[i]->triggered);

            //   events[i]->triggered = false; // Mark event as triggered
            // }
            // for (int i = 0; i < eventCount; i++) {
            //   Serial.print("Event : ");
            //   Serial.print(i);
            //   Serial.print(" - ");
            //   Serial.println(events[i]->triggered);
            // }

            // Serial.print("Trigger event: ");
            // Serial.print(i);
            // Serial.print(" - ");
            // Serial.println(events[i]->triggered);
        }

        
        for (int i = 0; i < eventCount; i++) {
          if (!events[i]->triggered && (dateTime.now.unixtime() >= events[i]->eventTime.unixtime())) {
              events[i]->triggered = true; // Mark event as triggered
              triggerEvent(i); // Trigger the event

              EventGen = i;                   // Evento de ejecución actual
              cycle = events[i]->cycle;
              CycleGen = cycle;               // Ciclo actual
              SyncGen = events[i]->synchrony; // Sincronía actual

              triggerEventFlag = true;
          }
        }
    }

    void triggerEvent(int eventIndex) {
        Serial.print("Event ");
        Serial.print(eventIndex); // Adjust for zero-based index to make it human-readable
        Serial.print(" triggered! -> ");
        Serial.println(events[eventIndex]->triggered);
        // Add specific actions for each event here
        // Class EVENT
    }

    void setScheduler() {
      // Schedule events 2 hours apart starting from 8:00 on January 1, 2024
      /*
      DateTime firstEvent(2024, 3, 25, 12, 12, 0);
      for (int i = 0; i < 8; i++) {
          scheduler.scheduleEvent(firstEvent + TimeSpan(0, 0, 2 * i, 0), 0, 0); // (DateTime, Cycle, Sincr)
      }
      */
      // Scheduler Set
      scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 1, 0, 0), 0, 0); // (DateTime, Cycle, Sincr)
      scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 2, 4, 0), 1, 10); // (DateTime, Cycle, Sincr)
      scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 4, 14, 0), 2, 30); // (DateTime, Cycle, Sincr)
      scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 5, 16, 0), 1, 10); // (DateTime, Cycle, Sincr)
      scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 6, 22, 0), 1, 0); // (DateTime, Cycle, Sincr)
      scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 7, 00, 0), 1, 10); // (DateTime, Cycle, Sincr)
      scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 16, 54, 0), 1, 0); // (DateTime, Cycle, Sincr)
      scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 17, 0, 0), 1, 0); // (DateTime, Cycle, Sincr)
      //delay(1000);
    }

    ~EventScheduler() {
        for (int i = 0; i < eventCount; i++) {
            delete events[i]; // Clean up dynamically allocated memory
        }
    }
};
EventScheduler scheduler;
/*
class DateTimePrinter {
public:
    void printCurrentDateTime() {
        DateTime now = rtc.now();
        char buf[20];
        sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
        Serial.println(buf);
    }
};
DateTimePrinter dateTimePrinter;
*/

class Events {
    private:
        int indHora;
        int indMinuto;
        int indCiclo;
        int indSincronia;

    public:
      Events () {

      }

      void print () {
        Serial.println("Escenarios:");
        for (int i = 0; i < 8; i++) {
          Serial.println("ReadConf::firstColumnValues[i]");
        }
      }
};
Events events;

//unsigned int ciclos[40][8], unsigned int sincronias[8], unsigned int horaMinutos[8][2]

class modFunc {
  private:
    // Función de interface 32 a 8 bits - en base a variables
    void interfaceProg(unsigned long var32Bits) {
        unsigned char var1 = (var32Bits & 0xFF) ^ 0xFF;
        unsigned char var2 = ((var32Bits >> 8) & 0xFF) ^ 0xFF;
        unsigned char var3 = ((var32Bits >> 16) & 0xFF) ^ 0xFF;
        unsigned char var4 = ((var32Bits >> 24) & 0xFF) ^ 0xFF;

        //ledWrite(var1,var2,var3,var4);
    }

    // Función de modo aislado
    void aislado(){
      
      //scheduler.checkAndTriggerEvents();
      exec.tiempoReal(&cycleArrayJson[0][0], progArrayJson, readconf.rowIndex, scheduler.cycle); // (Time, Esc, esc_long, cycle)
    }
    // Función de modo manual
    void manual(){
      exec.tiempoReal(&cycleArrayJson[0][0], progArrayJson, readconf.rowIndex, 0);
    }
    // Función de destello
    void destello(){
      exec.tiempoRealDestello(&timeBlinkRed[0], blinkRed, longitudTimeBlinkRed);
    }
    // Función de sincronización
    void sincronizado(){
    // Pendiente  
    }

  public:
    // Función de Modo
    void modofunc(){
      int lecturaBoton[CantidadBotonEntrada];
      static unsigned long startTime = 0; // To track when button 3 is pressed
      const unsigned long duration = 5000; // 5 seconds in milliseconds

      for (int i=0; i<CantidadBotonEntrada; i++){
        lecturaBoton[i] = digitalRead(botonEntrada[i]);

        if (lecturaBoton[i]==LOW && i==0 && estadoBoton[i] == LOW){ // Boton AP / WIFI
          estadoBoton[i] = HIGH;
          for (int i = 0; i<8; i++) {
            Serial.print("Event : ");
            Serial.print(i);
            Serial.print(" - ");
            Serial.print("triggered : ");
            Serial.print(scheduler.events[i]->triggered);
            Serial.print(" - ");
            Serial.print(scheduler.events[i]->eventTime.day());
            Serial.print("/");
            Serial.print(scheduler.events[i]->eventTime.month());
            Serial.print("/");
            Serial.print(scheduler.events[i]->eventTime.year());
            Serial.print(" - ");
            Serial.print(scheduler.events[i]->eventTime.hour());
            Serial.print(":");
            Serial.print(scheduler.events[i]->eventTime.minute());
            Serial.print(":");
            Serial.print(scheduler.events[i]->eventTime.second());
            Serial.print(" - ");
            Serial.print("ciclo: ");
            Serial.print(scheduler.events[i]->cycle);
            Serial.print(" - ");
            Serial.print("sincronia: ");
            Serial.println(scheduler.events[i]->synchrony);
          }
        }
        else if (lecturaBoton[i]==HIGH && i==0){
          estadoBoton[i] = LOW;
        }

        if (lecturaBoton[i]==LOW && i==1 && estadoBoton[i] == LOW){ // Botón Manual
          modo = 1; // Manual
          exec.indice++;
          estadoBoton[i] = HIGH;
          previousTime = millis();
          interfaceProg(*(progArrayJson + exec.indice));
        }
        else if (lecturaBoton[i]==HIGH && i==1){
          estadoBoton[i] = LOW;
        }

        if (lecturaBoton[i]==LOW && i==2 && estadoBoton[i] == LOW){ // Botón de destello
          modo = -1; // Destello
          exec.indice = 0;
          estadoBoton[i] = HIGH;
          previousTime = millis();
        }
        else if (lecturaBoton[i]==HIGH && i==2){
          estadoBoton[i] = LOW;
        }
        
        if (lecturaBoton[i] == LOW && i == 3 && estadoBoton[i] == LOW){ // Boton de restablecimiento
          modo = 3; // Prepare for Sicronizado mode, but wait for 30 seconds hold
          if (startTime == 0) { // If timer not already started, start it
            startTime = millis();
          }
          unsigned long currentTime = millis();
          if (currentTime - startTime >= duration) { // If button held for 5 seconds
            // Execute the process for button 3 here
            wm.resetSettings();
            ESP.restart();
            //startTime = 0; // Reset timer
          }
          //estadoBoton[i] = HIGH;
        } else if (lecturaBoton[i] == HIGH && i == 3){
          if (startTime != 0 && millis() - startTime < duration) { // If button released before 30 seconds
            // Process was not triggered, reset or handle accordingly
            startTime = 0; // Reset timer
          }
          estadoBoton[i] = LOW;
        }
      }
      // Modos de funcionamiento
      switch (modo){
        case -1:
            destello();
            estado = "Destello";
            break;
        case 0: //Aislado
            //Actualiza la máquina de estados
            aislado();
            estado = "Aislado";
            break;
        case 1: //Manual
            aislado();
            estado = "Manual";
            break;
        case 2: //Destello
            destello();
            estado = "Destello";
            break;
        case 3: //Sincronizado
            sincronizado();
            //estado = "Reset Wifi";
            break;
      }
    }
};
modFunc modos;