//////////////////////*Funciones*/////////////////////////


////*Función de interface de Registros de Desplazamiento*////
/*
void ledWrite(char Reg4, char Reg3, char Reg2, char Reg1){
   shiftOut(pinData, pinClock, LSBFIRST, Reg4);
   shiftOut(pinData, pinClock, LSBFIRST, Reg3);
   shiftOut(pinData, pinClock, LSBFIRST, Reg2);
   shiftOut(pinData, pinClock, LSBFIRST, Reg1);
   digitalWrite(pinLatch, HIGH);
   digitalWrite(pinLatch, LOW);
}*/

// Returns the number of milliseconds passed since the ESP32 chip was powered on or reset
unsigned long long millisESP32 () {
  return (unsigned long long) (esp_timer_get_time () / 1000ULL);
}



// Función de tiempo real
// void tiempoReal(unsigned int* time, unsigned long* prog, int longitud){
//   //Revisión de tiempo cumplido
//   if ( (millisESP32 () - previousTime >= *(time + indice)) ){
//     previousTime = millisESP32 ();
    
//     // Incrementar el índice en uno
//     indice++;
    
//     // Si el índice llega al final del arreglo, reiniciarlo a cero
//     if (indice >= longitud) {
//         indice = 0;
//     }
//     else {
//         // Ejecución de la Programación
//         interfaceProg(*(prog + indice));
//     }
//     /*Serial.print("Indice: ");
//     Serial.println(indice);*/
//   }
// }


void initWifi() {

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    //wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result
    oledtl.displayInfo("Conectando Wifi ...");
    delay(500);
    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    wm.setConfigPortalTimeout(ap_timeout);

    oledtl.displayInfo(String(ap_nameap));

    delay(1000);
    res = wm.autoConnect(ap_nameap, ap_passwordap); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        //wm.resetSettings();
        //ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        //Serial.println("connected...yeey :)");
        oledtl.displayInfo("IP: " + WiFi.localIP().toString());
    }
    
    WiFi.setTxPower(WIFI_POWER_MINUS_1dBm); // This sets the power to the lowest possible value
    //esp_wifi_set_max_tx_power(0); // Example: Set to a low value, you may need to adjust this
    
  delay(3000);
}





// Función de ejecución de proceso cada 1 s
/*
void timeProc01() {
  DateTime now = rtc.now();

  // Check if one second has passed
  if ((now.unixtime() - last_time.unixtime()) >= 1) {
    // Print message if time is up
    //Serial.println("Time's up!");
    digitalWrite (LED_PIN, !digitalRead (LED_PIN));

    //readGPS();
    //readRTC();

    // Update the last_time variable
    last_time = now;
  }
}*/



// Inicializa la pantalla OLED
void initOLED() {
  Wire.begin();	// inicializa bus I2C
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);	// inicializa pantalla con direccion 0x3C
  oled.clearDisplay();			// limpia pantalla
  oled.setTextColor(WHITE);		// establece color al unico disponible (pantalla monocromo)
  oled.setCursor(0, 0);			// ubica cursor en inicio de coordenadas 0,0
  oled.setTextSize(1);			// establece tamano de texto en 1
  oled.print("TrafficLight"); 	// escribe en pantalla el texto
  oled.display();			// muestra en pantalla todo lo establecido anteriormente

  /////////////////////OLED////////////////////////////
    oled.clearDisplay();			// limpia pantalla
  
    oled.drawBitmap(0, 0,  gImage_LOGOTL000, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(DELAY);
    oled.drawBitmap(0, 0,  gImage_LOGOTL00, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(DELAY);
    oled.drawBitmap(0, 0,  gImage_LOGOTL01, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(DELAY);
    oled.drawBitmap(0, 0,  gImage_LOGOTL02, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(DELAY);
    oled.drawBitmap(0, 0,  gImage_LOGOTL03, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(DELAY);
    oled.drawBitmap(0, 0,  gImage_LOGOTL04, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(DELAY);
    oled.drawBitmap(0, 0,  gImage_LOGOTL05, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(5000);
    oled.clearDisplay();			// limpia pantalla
    oled.drawBitmap(0, 0,  gImage_LOGOTL000, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(200);
    oled.drawBitmap(0, 0,  gImage_LOGOTL05, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(200);
    oled.clearDisplay();			// limpia pantalla
    oled.drawBitmap(0, 0,  gImage_LOGOTL000, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(200);
    oled.drawBitmap(0, 0,  gImage_LOGOTL05, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(200);
    oled.clearDisplay();			// limpia pantalla
    oled.drawBitmap(0, 0,  gImage_LOGOTL000, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(200);
    oled.drawBitmap(0, 0,  gImage_LOGOTL05, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(200);
    oled.clearDisplay();			// limpia pantalla
    oled.drawBitmap(0, 0,  gImage_LOGOTL, 128, 64, 1);
    oled.display();			// muestra en pantalla todo lo establecido anteriormente
    delay(5000);

}

// Función de inicialización del RTC
void initRTC() {
    // Initialize RTC
    if (!rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
    }

    // Store the current time
    //last_time = rtc.now();
    
    //DateTime now = rtc.now();

    // Print initialization message
    Serial.println("Inicio");

    dateTime.getCurrentDateTime(); // Print the current date and time
}

// Función de lectura de info de GPS
//void readGPS() {

  // This sketch displays information every time a new sentence is correctly encoded.
  //while (Serial1.available() > 0){
   //if (gps.encode(Serial1.read())) {
      // ano_gps = gps.date.year();
      // mes_gps = gps.date.month();
      // dia_gps = gps.date.day();
      // hora_gps = gps.time.hour();
      // minu_gps  = gps.time.minute(); 
      // sec_gps = gps.time.second();
      // centsec_gps = gps.time.centisecond();
      // lat = gps.location.lat();
      // lon = gps.location.lng();

      // ano_gps = year();
      // mes_gps = month();
      // dia_gps = day();
      // hora_gps = hour();
      // minu_gps  = minute(); 
      // sec_gps = second();
      // //centsec_gps = gps.time.centisecond();
      // lat = 0;//lat();
      // lon = 0;//gps.location.lng();
      
      //displayInfoGPS();
    //}
      
  //}
  
//}

// Función de lectura de info de GPS
/*
void readRTC() {
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  
}*/

// Función de Inicialización de GPS
void initGPS() {
  Serial1.begin(GPSBaud); 
  
}
/*
void getTime () {
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
    
}
*/
// Función que lista los directorios en la MicroSD
void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}
// Función que inicializa la tarjeta MicroSD
void initCard() {
  pinMode(4, OUTPUT);
  if(!SD.begin(4)){
        Serial.println("Card Mount Failed");
        return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
      Serial.println("No SD card attached");
      return;
  }

  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
      Serial.println("MMC");
  } else if(cardType == CARD_SD){
      Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
      Serial.println("SDHC");
  } else {
      Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

// Función que devuelve el número de líneas del archivo en MicroSD
int progLength (fs::FS &fs, const char * path) {
  int row = 0;

  File file = fs.open(path);
  if(!file){
      Serial.println("Failed to open file for reading");
      return 0;
  }

  while(file.available()){
      file.readStringUntil(';'); // read a line until newline character
      row++; // increment the row index
  }
  file.close();

  return row-1;
}

// Función que lee el archivo en MicroSD
void readFile(fs::FS &fs, const char * path){
    oledtl.showOLED(55);
    String line = ""; // to store each line
    int row = 0; // to keep track of the row index
    int col = 0; // to keep track of the column index

    int rows = 0;

    rows = progLength(SD, "/config/prog.txt");
    unsigned long matrix [rows] [2]; // to store the matrix, change the size as needed

    //Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    //Serial.println("Read from file: ");

    while(file.available()){
      //Serial.write(file.read());
      line = file.readStringUntil(';'); // read a line until newline character
      //Serial.print (line); // print the line for debugging
      //Serial.print (" - "); // print the line for debugging
      //Serial.println(line.length ()); // print the line for debugging
      col = 0; // reset the column index for each line
      for (int i = 0; i < line.length (); i++) { // loop through each character in the line
        if (line.charAt (i) == ',') { // if a comma is found
          matrix [row] [col] = strtoul (line.substring (0, i).c_str (), NULL, 10); // convert the substring before the comma to an unsigned long and store it in the matrix
          line = line.substring (i + 1); // remove the substring before the comma from the line
          i = 0; // reset the index to start from the beginning of the new line
          col++; // increment the column index
        }
      }
      matrix [row] [col] = strtoul (line.c_str (), NULL, 10); // convert the remaining substring to an unsigned long and store it in the matrix
      row++; // increment the row index
    }
    
    file.close();

    //Serial.println("Imprimiendo matriz:");
    // // print the matrix for debugging
    for (int i = 0; i < rows; i++) {
      //Serial.print(i);
      //Serial.print(" - ");
      for (int j = 0; j < 2; j++) {
        
        //Serial.print (matrix [i] [j], DEC); // print the matrix element in decimal format
        oledtl.showOLED(matrix [i] [j]);
        //Serial.print (" ");
      }
      //Serial.println ();
    }
}

void initThanks() {
  readFile(SD, "/config/prog.txt"); // Lectura de Prueba MicroSD

  myFile = SD.open("/config/ctrl.conf", FILE_READ);
  if (myFile) {
    Serial.println("ctrl.conf:");
    
    
    int row = 0; // Row counter
    while (myFile.available() && row < 8) {
      String line = myFile.readStringUntil('\n');
      int startPos = 0;
      int sepPos = line.indexOf(',', startPos);

      // Parse and store the first column
      unsigned long firstValue = strtoul(line.substring(startPos, sepPos).c_str(), NULL, 10);
      firstColumn[row] = firstValue;
      
      // Parse and store the remaining columns
      for (int col = 0; col < 8; col++) {
        startPos = sepPos + 1;
        sepPos = line.indexOf(',', startPos);
        if (sepPos == -1) sepPos = line.length(); // Handle the last value
        int value = line.substring(startPos, sepPos).toInt();
        matrix[row][col] = value;
      }
      
      Serial.print("Row ");
      Serial.print(row);
      Serial.print(": First Column = ");
      Serial.print(firstColumn[row]);
      Serial.print(", Other Columns = ");
      for (int col = 0; col < 8; col++) {
        Serial.print(matrix[row][col]);
        Serial.print(" ");
      }
      Serial.println();
      
      row++;
    }
    myFile.close();
  } else {
    Serial.println("error opening ctrl.conf");
  }

}

// Inicializa Botones de entrada
void initBot() {
  ////////////*Definición de pines como entrada*////////////
  for (int i=0; i<CantidadBotonEntrada; i++){
    pinMode(botonEntrada[i], INPUT);
  }
}

void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}


void gps_p() {
  unsigned long age;
  int Year;
  byte Month, Day, Hour, Minute, Second;

  while (Serial1.available()) {
    if (gps.encode(Serial1.read())) { // process gps messages
      // when TinyGPS reports new data...
      
      if (gps.location.isValid() && gps.date.isValid() && gps.time.isValid()) {
        // Get altitude
        //altitude = gps.location.lat(); // Altitude in meters latitude, longitude, altitude;
        // Get longitude
        latitude = gps.location.lat();
        // Get longitude
        longitude = gps.location.lng();
        // Get the number of satellites
        //satellites = gps.satellites();

        Month = gps.date.month();
        Day = gps.date.day();
        Year = gps.date.year();

        Hour = gps.time.hour();
        Minute = gps.time.minute();
        Second = gps.time.second();

        // set the Time to the latest GPS reading
        setTime(Hour, Minute, Second, Day, Month, Year);
        adjustTime(offset * SECS_PER_HOUR);

      }

    }
   
  }

  if (timeStatus()!= timeNotSet) {
    if (now() != prevDisplay) { //update the display only if the time has changed
      prevDisplay = now();


      gpsSecond = second();
      gpsDay = day();
      gpsMonth = month();
      gpsYear = year();
      gpsHour = hour();
      gpsMinute = minute();
        
      rtc.adjust(DateTime(gpsYear, gpsMonth, gpsDay, gpsHour, gpsMinute, gpsSecond));

  
    }
  }
}
///////////////////////////////Server////////////////////////////////////////
void handleLogin() {
  File file = SD.open("/web/index.html"); // Ensure the file exists on the SD card
  if (!file) {
    Serial.println("Failed to open file for reading");
    server.send(500, "text/plain", "Failed to load page");
    return;
  }

  String htmlContent;
  while (file.available()) {
    htmlContent += (char)file.read();
  }
  file.close();

  server.send(200, "text/html", htmlContent);
}

String generateToken() {
  String token = "";
  for (int i = 0; i < 16; ++i) {
    int randomType = random(0, 3); // Randomly choose between 3 types (number, uppercase, lowercase)
    char c;

    if (randomType == 0) {
      // Generate a number (0-9)
      c = (char)random(48, 58);
    } else if (randomType == 1) {
      // Generate an uppercase letter (A-Z)
      c = (char)random(65, 91);
    } else {
      // Generate a lowercase letter (a-z)
      c = (char)random(97, 123);
    }

    token += c;
  }
  return token;
}

void handleLoginCheck() {
  if (server.hasArg("username") && server.hasArg("password")) {
    if (server.arg("username") == loginUsername && server.arg("password") == loginPassword) {
      sessionToken = generateToken();
      server.sendHeader("Location", "/input?token=" + sessionToken);
      server.send(303);
    } else {
      server.send(401, "text/plain", "Unauthorized: Invalid credentials");
    }
  } else {
    server.send(400, "text/plain", "400: Invalid Request");
  }
}

void handleInput() {
  if (!server.hasArg("token") || server.arg("token") != sessionToken) {
    server.send(401, "text/plain", "Unauthorized");
    return;
  }
  
  File file = SD.open("/web/input.html"); // Ensure the file exists on the SD card
  if (!file) {
    Serial.println("Failed to open file for reading");
    server.send(500, "text/plain", "Failed to load page");
    return;
  }

  String htmlContent;
  while (file.available()) {
    htmlContent += (char)file.read();
  }
  file.close();

  server.send(200, "text/html", htmlContent);
}

void handleLogout() {
  sessionToken = generateToken(); // Clear the session token
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleSubmit() {
  // Retrieve GET parameters
  if (server.hasArg("num1") && server.hasArg("num2")) {
    unsigned long num1 = strtoul(server.arg("num1").c_str(), NULL, 10);
    unsigned long num2 = strtoul(server.arg("num2").c_str(), NULL, 10);

    // Do something with num1 and num2
    Serial.print("Number 1: ");
    Serial.println(num1);
    Serial.print("Number 2: ");
    Serial.println(num2);

    //Serial.println("Core #"+String(xPortGetCoreID()));

    // Redirect back to form
    server.sendHeader("Location", "/input?token="+sessionToken);
    server.send(303);
  } else {
    // If one of the parameters is missing, display an error
    server.send(400, "text/plain", "400: Invalid Request");
  }
}

void setupServer() {
  
  // // Define routes
  // server.on("/", HTTP_GET, handleLogin);
  // server.on("/login", HTTP_GET, handleLoginCheck);
  // server.on("/input", HTTP_GET, handleInput);
  // server.on("/submit", HTTP_GET, handleSubmit);
  // server.on("/logout", HTTP_GET, handleLogout); // Logout route

  // // Start server
  // server.begin();
  // Serial.println("HTTP server started");
}


//////////////////////////////////QTT/////////////////////////////////
/*
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
  }
  Serial.println();
}
*/

void callback(char* topic, byte* message, unsigned int length) {
  //Serial.print("Message arrived on topic: ");
  //Serial.print(topic);
  char* top = topic;
  //Serial.print(". Message: ");

  String messageTemp;

  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  //Serial.println(messageTemp);


  // Compare the topic and execute the appropriate code
  if (strcmp(topic, topicProg) == 0) {
    // Handle "sem/prog" topic
    //Serial.println("Message for sem/prog: " + messageTemp);
    // Deserialize the JSON document
    StaticJsonDocument<1024> doc; // Adjust size according to your JSON document complexity
    DeserializationError error = deserializeJson(doc, messageTemp);

    // Test if parsing succeeds.
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());
      return;
    }

    // Process the deserialized data (example)
    JsonObject escenarios = doc["escenarios"];
    JsonObject eventos = doc["eventos"];
    JsonObject ciclos = doc["ciclos"];
    JsonObject sincronias = doc["sincronias"];

    Serial.println("Escenarios:");
    for (JsonPair kv : escenarios) {
      const char* key = kv.key().c_str();
      JsonArray escenarioDetails = kv.value().as<JsonArray>();

      Serial.print("Escenario ");
      Serial.print(key);
      Serial.print(": ");
      
      for(int i = 0; i < escenarioDetails.size(); i++) {
        if (i > 0) Serial.print(", ");
        Serial.print(escenarioDetails[i].as<unsigned long>());
      }
      Serial.println();
    }

    // Add similar processing for eventos, ciclos, and sincronias as needed
    // Example of processing "eventos"
    //JsonObject eventos = doc["eventos"];
    Serial.println("Eventos:");
    for (JsonPair kv : eventos) {
      const char* key = kv.key().c_str();
      JsonArray eventDetails = kv.value().as<JsonArray>();

      Serial.print("Evento ");
      Serial.print(key);
      Serial.print(": ");
      
      // Assuming each event array contains [hour, minute, id, status]
      int hour = eventDetails[0]; // Hour
      int minute = eventDetails[1]; // Minute
      int ciclo = eventDetails[2]; // ID
      int sincronia = eventDetails[3]; // Status

      Serial.print("Hora: ");
      Serial.print(hour);
      Serial.print(":");
      Serial.print(minute);
      Serial.print(", Ciclo: ");
      Serial.print(ciclo);
      Serial.print(", Sincronía: ");
      Serial.println(sincronia);
    }


    Serial.println("Ciclos:");
    for (JsonPair kv : ciclos) {
      const char* key = kv.key().c_str();
      JsonArray cicloDetails = kv.value().as<JsonArray>();

      Serial.print("Ciclo ");
      Serial.print(key);
      Serial.print(": ");
      
      for(int i = 0; i < cicloDetails.size(); i++) {
        if (i > 0) Serial.print(", ");
        Serial.print(cicloDetails[i].as<int>());
      }
      Serial.println();
    }

    Serial.println("Sincronias:");
    for (JsonPair kv : sincronias) {
      const char* key = kv.key().c_str();
      JsonArray sincroniaDetails = kv.value().as<JsonArray>();

      Serial.print("Sincronia ");
      Serial.print(key);
      Serial.print(": ");
      
      for(int i = 0; i < sincroniaDetails.size(); i++) {
        if (i > 0) Serial.print(", ");
        Serial.print(sincroniaDetails[i].as<int>());
      }
      Serial.println();
  }
  } else if (strcmp(topic, topicCtrl) == 0) {
    // Handle "sem/ctrl" topic
    //Serial.println("Message for sem/ctrl: " + messageTemp);
    int messageInt = messageTemp.toInt(); // Converts the string to int

    switch (messageInt) {
      case -1:
        // Turn off WiFi
        WiFi.mode(WIFI_OFF);
        break;
      case 0:
        ESP.restart();
        break;
      case 1:
        wm.resetSettings();
        ESP.restart();
        break;
      case 2:
        modo = 0; // Aislado
        exec.indice = 0;
        break;
      case 3:
        modo = 1; // Manual
        break;
      case 4:
        modo = 2; // Destello
        exec.indice = 0;
        break;
      case 5:
        rtc.adjust(DateTime(gpsYear, gpsMonth, gpsDay, gpsHour, gpsMinute, gpsSecond));
        break;
      default:
        // statements
        break;
    }
    
  } else {
    // Handle default case
    Serial.println("Received message on an unknown topic.");
  }

  
}

void reconnect() {
  // Loop until reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(espClientMqtt)) {
      Serial.println("connected");
      //Serial.println("Core #"+String(xPortGetCoreID()));
      client.subscribe(topicProg);
      client.subscribe(topicCtrl);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/////////////////////////////////////////////////////////////////
// Timer handle
esp_timer_handle_t timerHandle;

// Structure to hold the callback argument data
struct CallbackData {
    int timesCalled;
    int maxCalls;
    String message;
};

// Callback function for the timer
void timerCallback(void* arg) {
    // Cast the argument back to the correct type
    CallbackData* data = static_cast<CallbackData*>(arg);

    // // Get the ID of the core running this callback
    // int coreID = xPortGetCoreID();
    // Serial.print("Core ");
    // Serial.print(coreID);
    // Serial.print(": ");
    // Serial.println(data->message);
  
    gps_p();
    dateTime.getCurrentDateTime(); // Print the current date and time

    dateTime.displayInfoGPS();

    // Stop the timer after a certain number of calls
    if (data->timesCalled == data->maxCalls) {
         //esp_timer_stop(timerHandle);
         //Serial.println("Timer stopped.");
         devices.sendStatus();
         data->timesCalled = 0;
    }
    data->timesCalled++;

    digitalWrite (exec.led_pin, !digitalRead (exec.led_pin));
   
}

void setTimerHandle() {
  ////////////////////////////////////////////*Timer Handle*//////////////////////////////////////////
  // Define the data to pass to the callback
  static CallbackData data = {
      .timesCalled = 0,
      .maxCalls = 80, // Stop the timer after 10 calls
      .message = "Timer callback triggered"
  };

  // Define the timer characteristics
  const esp_timer_create_args_t timerArgs = {
      .callback = &timerCallback,
      .arg = &data, // Pass the address of data as the argument
      .name = "MyTimer"
  };

  // Create the timer
  esp_timer_create(&timerArgs, &timerHandle);

  // Start the timer conditionally, for example, here we start immediately
  Serial.println("Starting timer...");
  esp_timer_start_periodic(timerHandle, 125000); // 1 second interval

  delay(500);
}