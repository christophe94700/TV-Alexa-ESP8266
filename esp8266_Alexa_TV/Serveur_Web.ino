
/* #####################################################
    #  Serveur web
##################################################### */



void init_server() {
    Serial.println("initialisation du serveur HTTP");
    server.onNotFound([]() {                              // If the client requests any URI
        if (!espalexa.handleAlexaApiCall(server.uri(), server.arg(0))) //if you don't know the URI, ask espalexa whether it is an Alexa control request
        if (!handleFileRead(server.uri()))                // send it if it exists
        server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
    });
    server.on("/set", srv_handle_set);                    // Serveur lecture des commandes depuis client
    server.on("/DateHeure", srv_handle_dateheure);        // Serveur pour affichage de la date et l'heure
    server.on("/IrCode", srv_handle_ircode);              // Serveur pour affichage du code IR
    server.on("/Etat", srv_handle_etat);                  // Serveur pour affichage des paramètres
    server.begin();                                       // Démarrage du serveur web
    Serial.println("Serveur HTTP démarré.");
    Serial.println("Serveur HTTP prêt");
}


String getContentType(String filename) { // convert the file extension to the MIME type
    if (filename.endsWith(".html")) return "text/html";
    else if (filename.endsWith(".css")) return "text/css";
    else if (filename.endsWith(".js")) return "application/javascript";
    else if (filename.endsWith(".ico")) return "image/x-icon";
    else if (filename.endsWith(".gz")) return "application/x-gzip";
    return "text/plain";
}

bool handleFileRead(String path) { // send the right file to the client (if it exists)
    Serial.println("handleFileRead: " + path);
    if ((path == "/parametres.html") and (Admin == 0)) return false;          // Blocage de l'accès aux paramètres
    for (int i = 1; i < 6; i++) {
        if ((path == ("/device" + String(i) + ".html")) and (Admin == 0)) return false; // Blocage de l'accès à la configuration des devices
    }
    if (path.endsWith("/")) path += "index.html"; // If a folder is requested, send the index file
    if (path == "/index.html") Admin = 0;                                    // Blocage de l'accès aux paramètres apres retour à la page de base
    String contentType = getContentType(path); // Get the MIME type
    String pathWithGz = path + ".gz";
    if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) { // If the file exists, either as a compressed archive, or normal
        if (SPIFFS.exists(pathWithGz)) // If there's a compressed version available
        path += ".gz"; // Use the compressed version
        File file = SPIFFS.open(path, "r"); // Open the file
        size_t sent = server.streamFile(file, contentType); // Send it to the client
        file.close(); // Close the file again
        Serial.println(String("\tSent file: ") + path);
        return true;
    }
    Serial.println(String("\tFile Not Found: ") + path);
    return false; // If the file doesn't exist, return false
}


void srv_handle_dateheure() {
    server.send(200, "text/plain", DateHeure);
}

void srv_handle_ircode() {
    server.send(200, "text/plain", IrCode);
}




// Reception des commandes depuis le client web

void srv_handle_set() {
    String WIFI_PASSWORD;
    String WIFI_IP;
    
    for (uint8_t i = 0; i < server.args(); i++) {
        // Réinitialisation
        if (server.argName(i) == "raz") {
            raz();
        }
        // WIFI SSID
        if (server.argName(i) == "ssid") {
            WIFI_SSID_G = (server.arg(i).c_str());
            Serial.println("Configuration Client Web SSID: " + WIFI_SSID_G);
        }
        // WIFI mot de passe
        if (server.argName(i) == "password") {
            WIFI_PASSWORD = (server.arg(i).c_str());
            Serial.println("Configuration Client Web Mdp: " + WIFI_PASSWORD);
            EcritureWifiEeprom(WIFI_SSID_G, WIFI_PASSWORD);
        }
        // WIFI IP FIXE ou DHCP
        if (server.argName(i) == "ipfixe") {
            WIFI_IP = (server.arg(i).c_str());
            EEPROM.write(ADRESS_RESEAU, 0);
            if (WIFI_IP != "0") {
                EEPROM.write(ADRESS_RESEAU, 1);
                EEPROM.write(ADRESS_RESEAU + 5, IPnum(WIFI_IP, 3));
            }
            EEPROM.commit();
            Serial.println("Configuration Client Web FIXE/DHCP: " + String(EEPROM.read(ADRESS_RESEAU)));
            Serial.println("Configuration Client Web IP FIXE: " + String(EEPROM.read(ADRESS_RESEAU + 5)));
        }
        // WIFI IP Passerelle
        if (server.argName(i) == "ippasse") {
            WIFI_IP = (server.arg(i).c_str());
            Serial.print("Configuration Client Web IP Passerelle: ");
            for (int i = 0; i < 4; ++i)
            {
                EEPROM.write(i + ADRESS_RESEAU + 1, IPnum(WIFI_IP, i));
                EEPROM.commit();
                Serial.print(String(EEPROM.read(i + ADRESS_RESEAU + 1)) + ".");
            }
            Serial.println("");
        }
        // IP MQTT SERVEUR
        if (server.argName(i) == "ipmqtt") {
            WIFI_IP = (server.arg(i).c_str());
            Serial.print("Configuration IP Serveur MQTT: ");
            for (int i = 0; i < 4; ++i)
            {
                EEPROM.write(i + ADRESS_MQTT_HOST, IPnum(WIFI_IP, i));
                EEPROM.commit();
                Serial.print(String(EEPROM.read(i + ADRESS_MQTT_HOST)) + ".");
            }
            Serial.println("");
        }
        // MQTT LOGIN
        if (server.argName(i) == "conxmqtt") {
            EcritureStringEeprom((server.arg(i).c_str()), ADRESS_MQTT_USER, 15);
            Serial.println("Configuration MQTT Connexion: " + LectureStringEeprom(ADRESS_MQTT_USER, 15));
        }
        // MQTT PWD
        if (server.argName(i) == "pwdmqtt") {
            EcritureStringEeprom((server.arg(i).c_str()), ADRESS_MQTT_PWD, 15);
            Serial.println("Configuration MQTT Password: " + LectureStringEeprom(ADRESS_MQTT_PWD, 15));
        }
        
        
        // Heure GMT
        if (server.argName(i) == "gmt") {
            int8_t tmp = (int8_t) strtol(server.arg(i).c_str(), NULL, 10);
            EEPROM.write(ADRESS_GMT, tmp);
            EEPROM.commit();
            tmp = EEPROM.read(ADRESS_GMT);
            if (tmp > -12 && tmp < 13) timeClient.setTimeOffset(3600 * tmp); // Initialisation du fuseau
            Serial.println("Configuration GMT: " + String(tmp));
        }
        // Nom du périphérique pour Alexa Commande Vocal
        if (server.argName(i) == "alexa1") {
            WIFI_SSID_G = (server.arg(i).c_str());
            EcritureStringEeprom((server.arg(i).c_str()), ADRESS_NOM_ALEXA1, 32);
            Serial.println("Configuration Nom périphérique Alexa: " + LectureStringEeprom(ADRESS_NOM_ALEXA1, 32));
        }
        if (server.argName(i) == "alexa2") {
            WIFI_SSID_G = (server.arg(i).c_str());
            EcritureStringEeprom((server.arg(i).c_str()), ADRESS_NOM_ALEXA2, 32);
            Serial.println("Configuration Nom périphérique Alexa: " + LectureStringEeprom(ADRESS_NOM_ALEXA2, 32));
        }
        // Mot de passe pour OTA et paramètrage
        if (server.argName(i) == "mdp") {
            WIFI_SSID_G = (server.arg(i).c_str());
            EcritureStringEeprom((server.arg(i).c_str()), ADRESS_PASSWORD, 32);
            Serial.println("Mot de passe pour OTA et paramètrage: " + LectureStringEeprom(ADRESS_PASSWORD, 32));
        }
        // Validation du mot de passe pour accès aux paramètres
        if (server.argName(i) == "login") {
            WIFI_SSID_G = (server.arg(i).c_str());
            //EcritureStringEeprom((server.arg(i).c_str()),ADRESS_PASSWORD,32);
            if (LectureStringEeprom(ADRESS_PASSWORD, 32) == WIFI_SSID_G) {
                Serial.println("Accès aux paramètres validés");
                Admin = true;
                } else {
                Serial.println("Accès aux paramètres invalidés");
                Admin = false;
            }
        }
        // Paramètrage IR
        if (server.argName(i) == "ircode") {
            Active_IrCode(String(server.arg(i).c_str()));
        }
        
        // Commande IR1 et IR2
        if (server.argName(i) == "device1") {                               // Marche arrêt IR1
            WIFI_SSID_G = (server.arg(i).c_str());
            if (WIFI_SSID_G == "on") {
                Ir_Envoi_On(1);
            }
            if (WIFI_SSID_G == "off") {
                Ir_Envoi_Off(1);
            }
            
        }
        if (server.argName(i) == "device2") {                                // Marche arrêt IR2
            WIFI_SSID_G = (server.arg(i).c_str());
            if (WIFI_SSID_G == "on") {
                Ir_Envoi_On(2);
            }
            if (WIFI_SSID_G == "off") {
                Ir_Envoi_Off(2);
            }
            
        }
    }
    server.send(200, "text/plain", "OK");
}


// Serveur pour la lecture des états
void srv_handle_etat() {
    String valeur;
    char buf[10];
    long temp;
    for (uint8_t i = 0; i < server.args(); i++) {
        // Etat MQTT
        if (server.argName(i) == "mqtt") {
            valeur = (server.arg(i).c_str());
            if (valeur == "ipmqtt") {
                server.send(200, "text/plain", ((String(EEPROM.read(ADRESS_MQTT_HOST))+"."+String(EEPROM.read(ADRESS_MQTT_HOST + 1))+"."+ String(EEPROM.read(ADRESS_MQTT_HOST + 2))+"."+String( EEPROM.read(ADRESS_MQTT_HOST + 3))).c_str()));        // Lecture IP serveur MQTT
            }  
            if (valeur == "commqtt") {
                server.send(200, "text/plain", ( LectureStringEeprom(ADRESS_MQTT_USER, 15)));        // Lecture Utilisateur MQTT
            }
            if (valeur == "in1mqtt") {
                server.send(200, "text/plain", ((NOM_HOST + String(ESP.getChipId())+ MQTT_TOPIC_IR1_GET).c_str()));        // Lecture Utilisateur MQTT
            } 
            if (valeur == "out1mqtt") {
                server.send(200, "text/plain", ((NOM_HOST + String(ESP.getChipId())+ MQTT_TOPIC_IR1_SET).c_str()));        // Lecture Utilisateur MQTT
            } 
            if (valeur == "in2mqtt") {
                server.send(200, "text/plain", ((NOM_HOST + String(ESP.getChipId())+ MQTT_TOPIC_IR2_GET).c_str()));        // Lecture Utilisateur MQTT
            } 
            if (valeur == "out2mqtt") {
                server.send(200, "text/plain", ((NOM_HOST + String(ESP.getChipId())+ MQTT_TOPIC_IR2_SET).c_str()));        // Lecture Utilisateur MQTT
            } 
        }
        // Etat wifi
        if (server.argName(i) == "wifi") {
            //valeur = (server.arg(i).c_str());
            valeur = (server.arg(i).c_str());
            if (valeur == "ssid") {
                server.send(200, "text/plain", (LectureWifiEeprom(1).c_str()));        // Lecture WIFI SSID
            }
            if (valeur == "ip") {
                server.send(200, "text/plain", (WiFi.localIP().toString().c_str()));  // Lecture WIFI IP
            }
            if (valeur == "routeur") {
                server.send(200, "text/plain", (WiFi.gatewayIP().toString().c_str())); // Lecture WIFI IP passerelle
            }
            if (valeur == "host") {
                server.send(200, "text/plain", ((NOM_HOST + String(ESP.getChipId())).c_str())); // Lecture WIFI hostname
            }
            if (valeur == "ipdns") {
                server.send(200, "text/plain", (WiFi.dnsIP().toString().c_str()));           // Lecture WIFI IP DNS
            }
            if (valeur == "mask") {
                server.send(200, "text/plain", (WiFi.subnetMask().toString().c_str()));     // Lecture WIFI masque sous reseau
            }
        }
        // Etat configuration
        if (server.argName(i) == "conf") {
            valeur = (server.arg(i).c_str());
            if (valeur == "gmt") {
                int8_t temp = EEPROM.read(ADRESS_GMT);;
                ltoa(temp, buf, 10);
                server.send(200, "text/plain", buf);        // Lecture valeur GMT
            }
            if (valeur == "alexa1") {
                server.send(200, "text/plain", (LectureStringEeprom(ADRESS_NOM_ALEXA1, 32)));       // Lecture valeur nom alexa
            }
            if (valeur == "alexa2") {
                server.send(200, "text/plain", (LectureStringEeprom(ADRESS_NOM_ALEXA2, 32)));       // Lecture valeur nom alexa
            }
        }
        // Etat conf IR Code
        if (server.argName(i) == "ir") {
            //valeur = (server.arg(i).c_str());
            valeur = (server.arg(i).c_str());
            if (valeur == "ir1") {
                server.send(200, "text/plain", EtatIr(0));        // Lecture Code IR
            }
            if (valeur == "ir2") {
                server.send(200, "text/plain", EtatIr(1));        // Lecture Code IR
            }
        }
    }
}
