
void Init_Mqtt(){
    // init la connexion au serveur MQTT
    IPAddress ip(EEPROM.read(ADRESS_MQTT_HOST ), EEPROM.read(ADRESS_MQTT_HOST + 1), EEPROM.read(ADRESS_MQTT_HOST + 2), EEPROM.read(ADRESS_MQTT_HOST + 3));
    Serial.println(ip);
    client.setServer(ip, 1883);                                                    // Initialisation serveur MQTT
    client.setCallback(callback);                                                  // Initialisation du retour
}

void Connect_Mqtt(){
    if (!client.connected()) {                       //MQTT
        if (timeClient.getSeconds()>50){                // Reconnexion au bout de 60 secondes à la 50 ieme secondes
            if (client.connect((NOM_HOST + String(ESP.getChipId())).c_str(),(LectureStringEeprom(ADRESS_MQTT_USER, 15)).c_str(),(LectureStringEeprom(ADRESS_MQTT_PWD, 15)).c_str())) {
                client.subscribe((NOM_HOST + String(ESP.getChipId()) + MQTT_TOPIC_IR1_SET).c_str()); // Client IR1
                client.subscribe((NOM_HOST + String(ESP.getChipId()) + MQTT_TOPIC_IR2_SET).c_str()); // Client IR2
                if (client.state()== 0){
                    sendState(1,0);
                    sendState(2,0);
                    Serial.println("MQTT Connexion...");
                }
            }
        }
        }else{
        client.loop(); 
    }    
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.println("Callback MQTT: ");
    char message[length + 1];
    for (int i = 0; i < length; i++) {
        message[i] = (char)payload[i];
    }
    message[length] = '\0';
    processJson(message,topic);
}

void processJson(char* message,char* topic) {
    DynamicJsonDocument doc(512);
    deserializeJson(doc, message);
    const char * val_etat = doc["state"];
    if (strcmp(topic,((NOM_HOST + String(ESP.getChipId())+ MQTT_TOPIC_IR1_SET).c_str()))==0){
        if (strcmp(val_etat, "ON") == 0){
            Serial.println("MQTT IR1: ON");
            Ir_Envoi_On(1);
        }
        if (strcmp(val_etat, "OFF") == 0){
            Serial.println("MQTT IR1: OFF");
            Ir_Envoi_Off(1);
        }
    }
    if (strcmp(topic,((NOM_HOST + String(ESP.getChipId())+ MQTT_TOPIC_IR2_SET).c_str()))==0){
        if (strcmp(val_etat, "ON") == 0){
            Serial.println("MQTT IR2: ON");
            Ir_Envoi_On(2);
        }
        if (strcmp(val_etat, "OFF") == 0){
            Serial.println("MQTT IR2: OFF");
            Ir_Envoi_Off(2);       
        }
    }
}

void sendState(uint8_t device,bool etat) {                                          // Transmission des états du bandeau
    if (client.state()== 0){
        char buffer[512];
        DynamicJsonDocument docMqtt(512);
        if (etat==0) {docMqtt["state"] ="OFF";} else {docMqtt["state"] ="ON";}
        size_t n = serializeJson(docMqtt, buffer);
        if (device==1){ client.publish((NOM_HOST + String(ESP.getChipId())+ MQTT_TOPIC_IR1_GET).c_str(), buffer, n);}
        if (device==2){ client.publish((NOM_HOST + String(ESP.getChipId())+ MQTT_TOPIC_IR2_GET).c_str(), buffer, n);}
        
        
    }
}
