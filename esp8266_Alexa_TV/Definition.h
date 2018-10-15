// QUICKFIX...See https://github.com/esp8266/Arduino/issues/263
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#define WIFI_TIMEOUT 60000                  // Vérification du WIFI toute les xxxx ms.
#define WIFIAP_TIMEOUT 1800000              // Temps de connexion en mode AP
#define WIFI_RESET 5                        // Reset du WIFI toute les xxxx minutes Valeur Max 255mn. Vauleur multiple de WIFI_TIMEOUT
#define HTTP_PORT 80                        // Port de connexion pour le serveur HTTP

#define ADRESS_EEPROM_INIT 7                // Adresse mémorisation de l'initialisation de EEPROM
#define ADRESS_WIFI 8                       // Adresse de départ paramètres WIFI Mot de passe et SSID (Fin ADRESS_WIFI + 96 mots)8-103
#define ADRESS_RESEAU 104                   // Adresse de départ paramètres Reseau DHCP=0 Fixe=1, IP passerelle,Fin IP statique (Fin ADRESS_RESEAU + 6 mots)104-109
#define ADRESS_GMT  117                     // Paramètre GMT heure été/hivers 1 mot

#define ADRESS_NOM_ALEXA1 200                // Paramètre Nom du périphérique pour Alexa 32 mots
#define ADRESS_NOM_ALEXA2 232                // Paramètre Nom du périphérique pour Alexa 32 mots
#define ADRESS_NOM_ALEXA3 264                // Paramètre Nom du périphérique pour Alexa 32 mots
#define ADRESS_NOM_ALEXA4 296                // Paramètre Nom du périphérique pour Alexa 32 mots
#define ADRESS_NOM_ALEXA5 328                // Paramètre Nom du périphérique pour Alexa 32 mots
#define ADRESS_NOM_ALEXA6 360                // Paramètre Nom du périphérique pour Alexa 32 mots
#define ADRESS_NOM_ALEXA7 392                // Paramètre Nom du périphérique pour Alexa 32 mots
#define ADRESS_NOM_ALEXA8 424                // Paramètre Nom du périphérique pour Alexa 32 mots
#define ADRESS_NOM_ALEXA9 456                // Paramètre Nom du périphérique pour Alexa 32 mots Adresse de fin-487




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
