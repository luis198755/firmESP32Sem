
// Librerías
#include <Arduino.h>
#include <ArduinoJson.h>
// -----------------------WifiManager---------------------------------
#include <WiFiManager.h>
#include <WiFi.h>
#include "esp_wifi.h"
// -----------------------Librerías para WebServer--------------------
#include <WebServer.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
// -----------------------Librerías para MQTT--------------------
#include <PubSubClient.h>
// -----------------------Librerías para Millis--------------------
#include <esp_timer.h>
// -----------------------Librerías microSD------------------------
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <stdlib.h>
// -----------------------Librerías I2C----------------------------
#include <Wire.h>			          
// -----------------------Librerías OLED----------------------------
#include <Adafruit_GFX.h>		    // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>		// libreria para controlador SSD1306
// -----------------------Librerías RTC----------------------------
#include "RTClib.h"
// -----------------------Librerías GPS----------------------------
#include <TimeLib.h>
#include <TinyGPS.h>      
// -------------------------------------------------------------------
// Archivos *.hpp - Fragmentar el Código
// -------------------------------------------------------------------
#include "settings.hpp"
#include "program.hpp"
#include "classes.hpp"
#include "functions.hpp"
#include "coreSettings.hpp"

//////////////*Void Setup*/////////////
void setup() {
  sessionToken = generateToken();
  //Inicialización del puerto serial del mCU
  Serial.begin(115200);
  
  //////////////////////INICIALIZACIÓN DE HARDWARE/////////////////////////
  initReg(); // Inicializa Registros
  initBot(); // Inicializa Botones
  Wire.begin();	// inicializa bus I2C
  
  initOLED(); // Pantalla
  initCard(); // MicroSD
  initRTC();  // Reloj de Tiempo Real
  initGPS();  // GPS

  readFile(SD, "/prog.txt"); // Lectura de Prueba MicroSD

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


  initWifi(); //Wifi
  // Definición de tarea en Core 0
  xTaskCreatePinnedToCore(webServerTask, "WebServerTask", 10000, NULL, 1, NULL, 0); // Run on Core 0
  
  delay(1000);
}
/////////////*Void Loop*/////////////
void loop() {
    
  // Lectura de Modo
  modofunc();

  //timeProc01(); 

}



