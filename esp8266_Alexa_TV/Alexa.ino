void InitAlexa() {
    if (EEPROM.read(ADRESS_NOM_ALEXA1) != 0) espalexa.addDevice(LectureStringEeprom(ADRESS_NOM_ALEXA1, 32), IrChange1); //Définition, etat arrêt
    Serial.print("Nom Alexa: ");
    Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA1, 32));
    if (EEPROM.read(ADRESS_NOM_ALEXA2) != 0) espalexa.addDevice(LectureStringEeprom(ADRESS_NOM_ALEXA2, 32), IrChange2); //Définition, etat arrêt
    Serial.print("Nom Alexa: ");
    Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA2, 32));
    espalexa.begin(&server);
}

//Retour Fonction Alexa
void IrChange1(uint8_t Ir1) {
    Serial.print("Changement d'état: ");
    Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA1, 32));
    
    if (Ir1) {
        Ir_Envoi_On(1);
        Serial.print("Commande Marche IR 1: ");
        
    }
    else  {
        Ir_Envoi_Off(1);
        Serial.println("Commande Arrêt IR 1: ");
        
    }
}

//Retour Fonction Alexa
void IrChange2(uint8_t Ir2) {
    Serial.print("Changement d'état: ");
    Serial.println(LectureStringEeprom(ADRESS_NOM_ALEXA2, 32));
    
    if (Ir2) {
        Serial.print("Commande Marche IR 2: ");
        Ir_Envoi_On(2);
        
    }
    else  {
        Serial.println("Commande Arrêt IR 2: ");
        Ir_Envoi_Off(2);
    }
}
