#include <ESP8266WiFi.h>                    //Inclusion bibliothèque gestion du WIFI de l'ESP8266
#include <Espalexa.h>                       //Inclusion bibliothèque pour commande avec Alexa Amazone
#include <ESP8266WebServer.h>               //Inclusion bibliothèque gestion du serveur web de l'ESP8266
#include <EEPROM.h>                         //Inclusion bibliothèque gestion de l'EEPROM
#include <FS.h>                             //Inclusion bibliothèque SPIFFS
#include <WiFiUdp.h>                        //Inclusion bibliothèque pour la gestion de l'User Datagram Protocol
#include <NTPClient.h>                      //Inclusion bibliothèque gestion serveur NTP
#include <ESP8266Ping.h>                    //Inclusion bibliothèque pour le ping et modification de byte count = 1 dans la bibliothèque
#include <StringSplitter.h>                 //Inclusion bibliothèque pour création d'un tableau depuis chaine avec séparateur Modifier nbrs MAX 5 => 10
#include "Definition.h"                     //Inclusion des définitions
#include <TimeLib.h>                        //Inclusion bibliothèque gestion des fonctionnalités de chronométrage
#include <IRremoteESP8266.h>                //Inclusion bibliothèque gestion Infrarouge
#include <IRsend.h>                         //Inclusion bibliothèque gestion Emission Infrarouge
#include <IRrecv.h>                         //Inclusion bibliothèque gestion Reception Infrarouge


extern "C" {
#include "user_interface.h"
}

// Variables globales
String DateHeure = "";                      // Variable pour gestion de la date et de l'heure
uint8_t ReseauOut = 0;                      // Variable Compteur Nombre de de perte du wifi
String WIFI_SSID_G = "";                    // Variable globale pour configuration SSID client Web
unsigned long Twifiap = 0;                   // Variable temps d'utilisation du mode WIFI AP
unsigned long last_wifi_check_time = 0;
String getContentType(String filename);     // convert the file extension to the MIME type
bool handleFileRead(String path);           // send the right file to the client (if it exists)
//IR
uint16_t rawData[67] = {4662, 4322,  686, 438,  652, 468,  622, 494,  598, 536,  562, 1676,  552, 566,  556, 560,  556, 560,  558, 558,  558, 558,  552, 564,  558, 560,  558, 1676,  560, 556,  558, 560,  556, 560,  560, 558,  552, 1684,  556, 1676,  562, 1676,  558, 1676,  556, 560,  564, 554,  560, 556,  562, 1674,  564, 552,  554, 564,  552, 564,  562, 554,  558, 1676,  554, 1680,  562, 1672,  562};  // SAMSUNG 8087887

//Instance des objets
ESP8266WebServer server(HTTP_PORT);
ADC_MODE(ADC_VCC);                        // utilisation de ESP.getVcc tension d'alimentation de l'esp

WiFiUDP ntpUDP;
// Vous pouvez spécifier le nom du serveur de temps et le décalage en secondes, peut être
// modifié plus tard avec setTimeOffset (). De plus, vous pouvez spécifier l'
// intervalle de mise à jour en millisecondes, avec setUpdateInterval ().
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void IrChange1(uint8_t Ir1);              // Retour des informations
void IrChange2(uint8_t Ir2);              // Retour des informations
Espalexa espalexa;

const uint8_t kIrLed = 0;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

void setup() {
  EEPROM.begin(512);                                //Initialise zone mémoire dans eeprom
  irsend.begin();                                   //Initialisation pour l'envois en IR
  InitEeprom();                                     //Initialisation EEprom apres effacement
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
  if (WiFi.status() == WL_CONNECTED) InitAlexa();                 // Initialisation d'Alexa
}


void loop() {
  conf_serie();                                        // Configuration via liaison série
  server.handleClient();
  delay(1);

  if (WiFi.status() == WL_CONNECTED) {                 // mode sur réseau WIFI avec routeur
    Date_Heure();
    wifi_verif();
    espalexa.loop();
    Twifiap = millis();
  } else {
    if (millis() - Twifiap > WIFIAP_TIMEOUT) {        // Temps en mode AP
      raz();
    }
  }

}

// Raz esp8266
void raz() {
  delay(500);
  WiFi.mode(WIFI_OFF);     // Arrêt du WIFI
  Serial.println("+++ Redémarrage du module +++");        //Saut de ligne
  ESP.restart();           // Redémarrage
}

