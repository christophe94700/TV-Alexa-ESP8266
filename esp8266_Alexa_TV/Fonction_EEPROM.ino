// Ecriture String EEPROM
void EcritureStringEeprom(String valeur, int adresse, int taille) {
  // Effacement de la zone mémoire
  for (int i = 0 ; i < taille; ++i) {
    EEPROM.write(i + adresse, 0);
  }
  EEPROM.commit();
  //Ecriture
  for (int i = 0; i < valeur.length(); ++i)
  {
    EEPROM.write(i + adresse, valeur[i]);
  }
  EEPROM.commit();
}

// Lecture String EEPROM
String LectureStringEeprom(int adresse, int taille)
{
  // Lecture de la valeur
  String valeur = "";
  for (int i = 0; i < taille; ++i)
  {
    if ((EEPROM.read(i + adresse)) == 0) return String(valeur);
    valeur += char(EEPROM.read(i + adresse));
  }
  return String(valeur);
}

// Effacement de la zone mémoire paramètres WIFI avant écriture
void EffaceWifiEeprom() {
  for (int i = ADRESS_WIFI ; i < ADRESS_WIFI + 96; ++i) {
    EEPROM.write(i, 0);
  }
}

// Initialisation des valeurs dans EEPROM
void InitEeprom(bool Force) {
  int8_t tmp = 0;
  tmp = EEPROM.read(ADRESS_EEPROM_INIT);
  if ((tmp != 20) or (Force == 1)) {
    // Efface EEPROM
    for (int i = 0; i < EEPROM.length(); ++i) {
      EEPROM.write(i, 0);
    }
    EcritureStringEeprom("Alexa" + String(ESP.getChipId()), ADRESS_NOM_ALEXA1, 32); // Defaut paramètres Alexa
    EcritureStringEeprom("admin", ADRESS_PASSWORD, 32);  // Defaut mots de passe mise à jour OTA
    EEPROM.write(ADRESS_EEPROM_INIT, 20);
    EEPROM.commit();
  }
  Serial.println("+++ Valeur par défaut EEPROM +++");        //Saut de ligne
}
