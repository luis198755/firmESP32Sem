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
  initOLED(); // Pantalla
  initCard(); // MicroSD
  initThanks();
  initRTC();  // Reloj de Tiempo Real
  initGPS();  // GPS
  initWifi(); //Wifi
  
  xTaskCreatePinnedToCore(webServerTask, "WebServerTask", 10000, NULL, 1, NULL, 0); // Run on Core 0// Definición de tarea en Core 0
  
  delay(500);
}
/////////////*Void Loop*/////////////
void loop() {
    
  // Lectura de Modo
  modofunc();

  //timeProc01(); 

}



