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
//#include <TinyGPS.h>      
//#include <TinyGPS++.h>
#include <TinyGPSPlus.h>


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


    setTimerHandle();
  
    xTaskCreatePinnedToCore(webServerTask, "WebServerTask", 10000, NULL, 1, NULL, 0); // Run on Core 0// Definición de tarea en Core 0
  
    scheduler.setScheduler();

}
/////////////*Void Loop*/////////////
void loop() {
  
    scheduler.checkAndTriggerEvents();

    // Lectura de Modo
    modos.modofunc();

}



