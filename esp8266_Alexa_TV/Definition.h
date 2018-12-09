// QUICKFIX...See https://github.com/esp8266/Arduino/issues/263
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

// Configuration des entrées/sorties
#define EmIrLed 0                           // ESP8266 GPIO utilisé pour l'émission. (D3).
#define ReIrLed 2                           // ESP8266 GPIO utilisé pour la réception (D4).

// Paramètres réseau
#define WIFI_TIMEOUT 60000                  // Vérification du WIFI toute les xxxx ms.
#define WIFIAP_TIMEOUT 1800000              // Temps de connexion en mode AP
#define WIFI_RESET 5                        // Reset du WIFI toute les xxxx minutes Valeur Max 255mn. Vauleur multiple de WIFI_TIMEOUT
#define HTTP_PORT 80                        // Port de connexion pour le serveur HTTP
// Adressage EEPROM
#define ADRESS_EEPROM_INIT 7                // Adresse mémorisation de l'initialisation de EEPROM
#define ADRESS_WIFI 8                       // Adresse de départ paramètres WIFI Mot de passe et SSID (Fin ADRESS_WIFI + 96 mots)8-103
#define ADRESS_RESEAU 104                   // Adresse de départ paramètres Reseau DHCP=0 Fixe=1, IP passerelle,Fin IP statique (Fin ADRESS_RESEAU + 6 mots)104-109
#define ADRESS_GMT  110                     // Paramètre GMT heure été/hivers 1 mot
#define ADRESS_PASSWORD 111                // Paramètre Nom du périphérique pour OTA et accès paramètres 32 mots 111-142

#define ADRESS_NOM_ALEXA1 200                // Paramètre Nom du périphérique 1 pour Alexa 32 mots 200-231
#define ADRESS_NOM_ALEXA2 232                // Paramètre Nom du périphérique 2 pour Alexa 32 mots 232-263

#define ADRESS_IR_10 300                    // Pramètres IR périphérique 1 IR0 Code 4 mots,Protoco 1,nbit 1,répétion 1,Mode 1 mot  8 mots 300-307
#define ADRESS_IR_11 308                    // Pramètres IR périphérique 1 IR1 8 mots 307-315
#define ADRESS_IR_12 316                    // Pramètres IR périphérique 1 IR2 8 mots 316-323
#define ADRESS_IR_13 324                    // Pramètres IR périphérique 1 IR3 8 mots 324-331
#define ADRESS_IR_14 332                    // Pramètres IR périphérique 1 IR7 8 mots 332-339

#define ADRESS_IR_20 340                    // Pramètres IR périphérique 2 IR0 8 mots 340-347
#define ADRESS_IR_21 348                    // Pramètres IR périphérique 2 IR1 8 mots 348-355
#define ADRESS_IR_22 356                    // Pramètres IR périphérique 2 IR2 8 mots 356-363
#define ADRESS_IR_23 364                    // Pramètres IR périphérique 2 IR3 8 mots 364-371
#define ADRESS_IR_24 372                    // Pramètres IR périphérique 2 IR7 8 mots 372-380
// Paramètres
#define IR_Mots 8         // Nombre de mot par paramètre
#define Nbrs_Para_IR 7         // Nombre de paramètre envoyer
// Valeur par défaut EEPROM

#define DEF_GMT  0                     // Paramètre GMT heure été/hivers 

#define S_REASON_FOR_RESTART "\nRaison du démarrage: (%d) getResetReason: %s\n\n"
#define S_POWER_ON           "Mis sous tension."
#define S_HARDWARE_WD        "Déclenchement du chien de garde matériel."
#define S_EXCEPTION_OCCURED  "Occurence d'une exception.\n"
#define S_SOFTWARE_WD        "Déclanchement du chien de garde logiciel."
#define S_RESTART_OR_RESET   "Fonction restart() ou reset() invoquée."
#define S_ESP_WOKE           "Réveil du ESP après un profond sommeil."
#define S_EXTERNAL_RESET     "Réinitialisation externe du système."
#define S_UNKNOWN_REASON     "Pour une raison inconnue."

#define S_RST_RESTART "\n\nRedémarrage avec ESP.restart()"
#define S_RST_RESET "\n\nRedémarrage avec ESP.reset()"
#define S_RST_HWDT "\n\nRedémarrage avec déclenchement du chien de garde matériel (attendre 6 secondes)"
#define S_RST_SWDT "\n\nRedémarrage avec déclenchement du chien de garde logociel (attendre 3 seconds)"
#define S_RST_EXCP_0 "\n\nRedémarrage en vertu de l'exception 0: IllegalInstructionCause (division par 0)"
#define S_RST_EXCP_3 "\n\nRedémarrage en vertu de l'exception 3: LoadStoreErrorCause"
