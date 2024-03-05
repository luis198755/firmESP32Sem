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

#include "settingsReset.hpp"
#include "settingsRead.hpp"
#include "settingsSave.hpp"

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
  exec.initReg(); // Inicializa Registros
  initBot(); // Inicializa Botones
  initOLED(); // Pantalla
  initCard(); // MicroSD
  
  readconf.readConf();
  readconf.printArraysProv();
  
  // Lee la Configuración WiFi
  if(!settingsReadWiFi()){        
      // Salvar las configuraciones del WIFI
      settingsSaveWiFi();
  }
  
  initThanks();
  initRTC();  // Reloj de Tiempo Real
  initGPS();  // GPS
  initWifi(); //Wifi
  
  xTaskCreatePinnedToCore(webServerTask, "WebServerTask", 10000, NULL, 1, NULL, 0); // Run on Core 0// Definición de tarea en Core 0
  
  // Schedule events 2 hours apart starting from 8:00 on January 1, 2024
  DateTime firstEvent(2024, 3, 5, 12, 54, 0);
  for (int i = 0; i < 8; i++) {
      scheduler.scheduleEvent(firstEvent + TimeSpan(0, 0, 1 * i, 0));
  }

  delay(500);
}
/////////////*Void Loop*/////////////
void loop() {
  
  // Lectura de Modo
  modofunc();

  //timeProc01(); 

}



