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
#include "settingsReset.hpp"
#include "settingsRead.hpp"
#include "settingsSave.hpp"


#include "classes.hpp"
#include "functions.hpp"
#include "coreSettings.hpp"

//////////////*Void Setup*/////////////
void setup() {
  sessionToken = generateToken();
  //Inicialización del puerto serial del mCU
  Serial.begin(115200);
  
  //////////////////////INICIALIZACIÓN DE HARDWARE/////////////////////////
  exec.initReg(); // Inicializa Registros
  initBot(); // Inicializa Botones
  initOLED(); // Pantalla
  initCard(); // MicroSD
  
  readconf.readConf();
  readconf.printArraysProv();

  Serial.print("size: ");
  Serial.println(readconf.rowIndex);
  
  // Lee la Configuración WiFi
  if(!settingsReadWiFi()){        
      // Salvar las configuraciones del WIFI
      settingsSaveWiFi();
  }

  settingsReadProg();
  
  initThanks();
  initRTC();  // Reloj de Tiempo Real
  initGPS();  // GPS
  initWifi(); //Wifi

  delay(500);
  
  xTaskCreatePinnedToCore(webServerTask, "WebServerTask", 10000, NULL, 1, NULL, 0); // Run on Core 0// Definición de tarea en Core 0
  
  // Schedule events 2 hours apart starting from 8:00 on January 1, 2024
  /*
  DateTime firstEvent(2024, 3, 25, 12, 12, 0);
  for (int i = 0; i < 8; i++) {
      scheduler.scheduleEvent(firstEvent + TimeSpan(0, 0, 2 * i, 0), 0, 0); // (DateTime, Cycle, Sincr)
  }
  */
  dateTime.getCurrentDateTime(); // Print the current date and time
  scheduler.scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 5, 0, 0), 0, 0); // (DateTime, Cycle, Sincr)
  scheduler.scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 14, 26, 0), 1, 10); // (DateTime, Cycle, Sincr)
  scheduler.scheduleEvent(DateTime(rtcYear, rtcMonth, rtcDay, 16, 48, 0), 2, 30); // (DateTime, Cycle, Sincr)
  delay(1000);
  
}
/////////////*Void Loop*/////////////
void loop() {
  
    scheduler.checkAndTriggerEvents();

    // Lectura de Modo
    modos.modofunc();

    // if (rtcSecond == 0 && flagSecond == 0) {
    //      previousTime = millis();
    //      minuteflag = rtcMinute;
    //      flagSecond = 1;
    //      Serial.println("xxxx");
    //      if (rtcMinute != minuteflag) {
    //         flagSecond = 0;
    //             Serial.println("yyyyy");
    //      }
    // }
      
    //dateTime.getCurrentDateTime(); // Print the current date and time
    //timeProc01(); 
}



