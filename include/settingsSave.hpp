// -------------------------------------------------------------------
// Guardar las configuraciones del WIFI y Generales
// -------------------------------------------------------------------
boolean settingsSaveWiFi(){
    // Graba configuración del WiFi y General
    StaticJsonDocument<768> jsonConfig;

    myFile = SD.open("/config/settingwifi.json", FILE_WRITE);
    if (myFile){
        /* ------------------- GENERAL -------------------- */
        jsonConfig["id"] = idDevice;
        /* ------------------- CLIENTE -------------------- */
        jsonConfig["wifi_ssid"] = wifi_ssid;
        jsonConfig["wifi_passw"] = wifi_passw;
        /* ------------------- AP ------------------------- */
        jsonConfig["ap_accessPoint"] = ap_accessPoint;
        jsonConfig["ap_nameap"] = ap_nameap;
        jsonConfig["ap_passwordap"] = ap_passwordap;
        jsonConfig["ap_canalap"] = ap_canalap;
        jsonConfig["ap_hiddenap"] = ap_hiddenap;
        jsonConfig["ap_connetap"] = ap_connetap;
        serializeJsonPretty(jsonConfig, myFile);
        myFile.close();
        Serial.println("Info: Configuración WiFi Guardada");
        //serializeJsonPretty(jsonConfig, Serial);   
        return true;
    }else{
        Serial.println("Error: Falló el guardado de la configuración WiFI");
        return false;
    }    
}