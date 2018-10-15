void InitAlexa() {
  if (EEPROM.read(ADRESS_NOM_ALEXA1) != 0) espalexa.addDevice(LectureStringEeprom(ADRESS_NOM_ALEXA1, 32), IrChange1); //Définition, etat arrêt
  Serial.print("Nom Alexa: ");
  Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA1, 32));
  if (EEPROM.read(ADRESS_NOM_ALEXA2) != 0) espalexa.addDevice(LectureStringEeprom(ADRESS_NOM_ALEXA2, 32), IrChange2); //Définition, etat arrêt
  Serial.print("Nom Alexa: ");
  Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA2, 32));
 /* if (EEPROM.read(ADRESS_NOM_ALEXA3) == 0) espalexa.addDevice(LectureStringEeprom(ADRESS_NOM_ALEXA3, 32), IrChange3); //Définition, etat arrêt
  Serial.print("Nom Alexa: ");
  Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA3, 32));
  if (EEPROM.read(ADRESS_NOM_ALEXA4) == 0) espalexa.addDevice(LectureStringEeprom(ADRESS_NOM_ALEXA4, 32), IrChange4); //Définition, etat arrêt
  Serial.print("Nom Alexa: ");
  Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA4, 32));
  if (EEPROM.read(ADRESS_NOM_ALEXA5) == 0) espalexa.addDevice(LectureStringEeprom(ADRESS_NOM_ALEXA5, 32), IrChange5); //Définition, etat arrêt
  Serial.print("Nom Alexa: ");
  Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA5, 32));
  if (EEPROM.read(ADRESS_NOM_ALEXA6) == 0) espalexa.addDevice(LectureStringEeprom(ADRESS_NOM_ALEXA6, 32), IrChange6); //Définition, etat arrêt
  Serial.print("Nom Alexa: ");
  Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA6, 32));
  if (EEPROM.read(ADRESS_NOM_ALEXA7) == 0) espalexa.addDevice(LectureStringEeprom(ADRESS_NOM_ALEXA7, 32), IrChange7); //Définition, etat arrêt
  Serial.print("Nom Alexa: ");
  Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA7, 32));
  if (EEPROM.read(ADRESS_NOM_ALEXA8) == 0) espalexa.addDevice(LectureStringEeprom(ADRESS_NOM_ALEXA8, 32), IrChange8); //Définition, etat arrêt
  Serial.print("Nom Alexa: ");
  Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA8, 32));
  if (EEPROM.read(ADRESS_NOM_ALEXA9) == 0) espalexa.addDevice(LectureStringEeprom(ADRESS_NOM_ALEXA9, 32), IrChange9); //Définition, etat arrêt
  Serial.print("Nom Alexa: ");
  Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA9, 32));
  if (EEPROM.read(ADRESS_NOM_ALEXA10) == 0) espalexa.addDevice(LectureStringEeprom(ADRESS_NOM_ALEXA10, 32), IrChange10); //Définition, etat arrêt
  Serial.print("Nom Alexa: ");
  Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA10, 32));*/
  espalexa.begin(&server);
}
//Retour Fonction Alexa
void IrChange1(uint8_t Ir1) {
  Serial.print("Changement d'état: ");
  Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA1, 32));

  if (Ir1) {
    Ir_Envoi_On();
    Serial.print("Commande Marche IR 1: ");

  }
  else  {
    Ir_Envoi_Off();
    Serial.println("Commande Arrêt IR 1: ");

  }
}

//Retour Fonction Alexa
void IrChange2(uint8_t Ir2) {
  Serial.print("Changement d'état: ");
  Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA2, 32));

  if (Ir2) {
    Serial.print("Commande Marche IR 2: ");
    Ir_Envoi_vol(Ir2);

  }
  else  {
    Serial.println("Commande Arrêt IR 2: ");
  }
}
