// -------------------------------------------------------------------
// Leer configuraciones de los Parametros WIFI
// -------------------------------------------------------------------
boolean settingsReadWiFi(){
    
    //StaticJsonDocument<768> jsonConfig;    
    StaticJsonDocument<768> jsonConfig;

    myFile = SD.open("/config/settingwifi.json", FILE_READ);
    if (myFile) {
        Serial.println("ctrl.conf:");
        if(deserializeJson(jsonConfig, myFile)){
            // Si falla la lectura inicia valores por defecto
            settingsResetWiFi();
            Serial.println("Error: Falló la lectura de la configuración WiFi, tomando valores por defecto");
            return false;
        }else{
            /* ------------------- GENERAL -------------------- */
            strlcpy(idDevice, jsonConfig["id"], sizeof(idDevice)); 
            /* ------------------- CLIENTE -------------------- */
            strlcpy(wifi_ssid, jsonConfig["wifi_ssid"], sizeof(wifi_ssid));
            strlcpy(wifi_passw, jsonConfig["wifi_passw"], sizeof(wifi_passw));        
            /* ------------------- AP ------------------------ */
            ap_accessPoint = jsonConfig["ap_accessPoint"];
            strlcpy(ap_nameap, jsonConfig["ap_nameap"], sizeof(ap_nameap));
            strlcpy(ap_passwordap, jsonConfig["ap_passwordap"], sizeof(ap_passwordap));
            ap_canalap = jsonConfig["ap_canalap"];
            ap_hiddenap = jsonConfig["ap_hiddenap"];
            ap_connetap = jsonConfig["ap_connetap"];
            myFile.close();
            Serial.println("Info: Lectura configuración WiFi correcta");
            return true;
        }
    }
}

// -------------------------------------------------------------------
// Leer configuraciones de los Parametros de Programación
// -------------------------------------------------------------------
boolean settingsReadProg(){
    
    //StaticJsonDocument<768> jsonConfig;    
    StaticJsonDocument<768> jsonConfig;

    myFile = SD.open("/config/prog.json", FILE_READ);
    if (myFile) {
        Serial.println("prog.conf:");
        if(deserializeJson(jsonConfig, myFile)){
            // Si falla la lectura inicia valores por defecto
            //settingsResetWiFi();
            Serial.println("Error: Falló la lectura de la configuración de Programación, tomando valores por defecto");
            return false;
        }else{
            
            Serial.println("dataJson: ");
            for (int i=0; i <= 30; i++) {
                prog00[i] = jsonConfig["escenarios"]["1"][i];
                Serial.println(prog00[i]);
            }
            
            myFile.close();
            Serial.println("Info: Lectura configuración de Programa correcta");
            return true;
        }
    }
}