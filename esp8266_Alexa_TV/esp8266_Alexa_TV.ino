#include <ESP8266WiFi.h>                    //Inclusion bibliothèque gestion du WIFI de l'ESP8266
#include <ESP8266mDNS.h>                    // Inclusion bibliothèque mDNS
#include <Espalexa.h>                       //Inclusion bibliothèque pour commande avec Alexa Amazone
#include <ESP8266WebServer.h>               //Inclusion bibliothèque gestion du serveur web de l'ESP8266
#include <EEPROM.h>                         //Inclusion bibliothèque gestion de l'EEPROM
#include <FS.h>                             //Inclusion bibliothèque SPIFFS
#include <WiFiUdp.h>                        //Inclusion bibliothèque pour la gestion de l'User Datagram Protocol
#include <ArduinoOTA.h>                     //Inclusion bibliothèque pour mise à via le WIFI
#include <NTPClient.h>                      //Inclusion bibliothèque gestion serveur NTP
#include <Pinger.h>                         //Inclusion bibliothèque pour le ping
#include <StringSplitter.h>                 //Inclusion bibliothèque pour création d'un tableau depuis chaine avec séparateur Modifier nbrs MAX 5 => 10
#include <TimeLib.h>                        //Inclusion bibliothèque gestion des fonctionnalités de chronométrage
#include <IRremoteESP8266.h>                //Inclusion bibliothèque gestion Infrarouge
#include <IRsend.h>                         //Inclusion bibliothèque gestion Emission Infrarouge
#include <IRrecv.h>                         //Inclusion bibliothèque gestion Reception Infrarouge
#include <PubSubClient.h>                   //Inclusion bibliothèque pour la gestion des messages MQTT
#include <ArduinoJson.h>                    //Inclusion bibliothèque pour la gestion du format Json

#include "Definition.h"                     //Inclusion des définitions

extern "C" {
    #include "user_interface.h"
    #include <lwip/icmp.h> // needed for icmp packet definitions
}

// Variables globales
String DateHeure = "";                      // Variable pour gestion de la date et de l'heure
String IrCode = "";                      // Variable pour gestion de la date et de l'heure
uint8_t ReseauOut = 0;                      // Variable Compteur Nombre de de perte du wifi
String WIFI_SSID_G = "";                    // Variable globale pour configuration SSID client Web
unsigned long Twifiap = 0;                   // Variable temps d'utilisation du mode WIFI AP
unsigned long last_wifi_check_time = 0;
String getContentType(String filename);     // convert the file extension to the MIME type
bool handleFileRead(String path);           // send the right file to the client (if it exists)
bool Admin = 0;                             // 0= pas de login 1=login validé

//Instance des objets
ESP8266WebServer server(HTTP_PORT);
ADC_MODE(ADC_VCC);                        // utilisation de ESP.getVcc tension d'alimentation de l'esp

WiFiUDP ntpUDP;
// Vous pouvez spécifier le nom du serveur de temps et le décalage en secondes, peut être
// modifié plus tard avec setTimeOffset (). De plus, vous pouvez spécifier l'
// intervalle de mise à jour en millisecondes, avec setUpdateInterval ().
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 3600000);

void IrChange1(uint8_t Ir1);              // Retour des informations
void IrChange2(uint8_t Ir2);              // Retour des informations
Espalexa espalexa;
// Liste des code IR
const char *pointer[] PROGMEM = { "UNKNOWN", "UNUSED", "RC5", "RC6", "NEC", "SONY", "PANASONIC", "JVC", "SAMSUNG", "WHYNTER", "AIWA_RC_T501", "LG", "SANYO", "MITSUBISHI", "DISH", "SHARP", "COOLIX", "DAIKIN", "DENON", "KELVINATOR", "SHERWOOD", "MITSUBISHI_AC", "RCMM", "SANYO_LC7461", "RC5X", "GREE", "PRONTO", "NEC_LIKE", "ARGO", "TROTEC", "NIKAI", "RAW", "GLOBALCACHE", "TOSHIBA_AC", "FUJITSU_AC", "MIDEA", "MAGIQUEST", "LASERTAG", "CARRIER_AC", "HAIER_AC", "MITSUBISHI2", "HITACHI_AC", "HITACHI_AC1", "HITACHI_AC2", "GICABLE", "HAIER_AC_YRW02", "WHIRLPOOL_AC", "SAMSUNG_AC", "LUTRON", "ELECTRA_AC", "PANASONIC_AC", "PIONEER", "LG2", "MWM"};

IRsend irsend(EmIrLed);  // Set the GPIO to be used to sending the message.
IRrecv irrecv(ReIrLed);
decode_results results;

WiFiClient espClient;
PubSubClient client(espClient);

Pinger pinger;

void setup() {
    EEPROM.begin(512);                                //Initialise zone mémoire dans eeprom
    irsend.begin();                                   //Initialisation pour l'envois en IR
    irrecv.enableIRIn();                              //Démarrage pour la réception signaux Infra rouge
    InitEeprom(0);                                    //Initialisation EEprom apres effacement
    Serial.begin(115200);                             //Vitesse liaison série 115200
    Info_reboot();                                    // Information sur l'origine du reboot
    Info_ESP();                                       // Information esp8266
    wifi_setup();                                                   // Initialisation du wifi
    int8_t tmp = EEPROM.read(ADRESS_GMT);                           // Lecture du fuseau horaire
    if (tmp > -12 && tmp < 13) timeClient.setTimeOffset(3600 * tmp);// Initialisation du fuseau
    timeClient.begin();                                             // Démarrage du client NTP
    SPIFFS.begin();                                                 // Démarrage du SPI Flash Files System
    init_server();                                                  // Initialisation des serveurs
    Date_Heure();                                                   // initialisation de la date et de l'heure
    Twifiap = millis();                                             // Initialisation du temps en mode AP
    if (WiFi.status() == WL_CONNECTED) {                            // Initialisation si connexion WIFI
        InitAlexa();                                                  // Initialisation d'Alexa
        Init_Mqtt();                                                  // Initialisation MQTT
        ArduinoOTA.setHostname(("MyTV" + String(ESP.getChipId())).c_str());          // Nom du module pour mise à jour et pour le mDNS
        ArduinoOTA.setPassword((LectureStringEeprom(ADRESS_PASSWORD, 32)).c_str());  // Mot de passe pour mise à jour
        ArduinoOTA.onEnd([]() {                                                      // Effacement EEPROM après mise à jour
            InitEeprom(1);
        });
        ArduinoOTA.begin();                                                           // Initialisation de l'OTA
    }else {init_server();} 
}


void loop() {
    conf_serie();                                        // Configuration via liaison série
    delay(1);
    if (WiFi.status() == WL_CONNECTED) {                 // mode sur réseau WIFI avec routeur
        Date_Heure();
        wifi_verif();
        espalexa.loop();
        Twifiap = millis();
        if(EEPROM.read(ADRESS_MQTT_HOST )!=0) Connect_Mqtt();                              //MQTT
        ArduinoOTA.handle();
        } else {
        server.handleClient();                            // Serveurs en mode AP
        if (millis() - Twifiap > WIFIAP_TIMEOUT) {        // Temps en mode AP
            raz();
        }
    }
    
    // Decodage IR
    if (irrecv.decode(&results)) {
        dump(&results);
        irrecv.resume();  // Receive the next value
    }
}

// Raz esp8266
void raz() {
    delay(500);
    WiFi.mode(WIFI_OFF);     // Arrêt du WIFI
    Serial.println("+++ Redémarrage du module +++");        //Saut de ligne
    ESP.restart();           // Redémarrage
}
