// -------------------------------------------------------------------
// Valores por defecto Parametros WIFI
// -------------------------------------------------------------------
void settingsResetWiFi(){
    /* ------------------- GENERAL -------------------- */
    strlcpy(idDevice, "adminesp32", sizeof(idDevice));
    /* ------------------- CLIENTE -------------------- */
    strlcpy(wifi_ssid, "iotmaster", sizeof(wifi_ssid));
    strlcpy(wifi_passw, "iotmaster84", sizeof(wifi_passw));
    strlcpy(wifi_ip_static, "192.168.20.180", sizeof(wifi_ip_static));
    
    /* ------------------- AP ------------------------- */
    ap_accessPoint = false;
    strlcpy(ap_nameap, "tlmx", sizeof(ap_nameap));
    strlcpy(ap_passwordap, "123456789", sizeof(ap_passwordap));
    ap_canalap = 9;         
    ap_hiddenap = false;        
    ap_connetap = 1;
    ap_timeout = 60;
}