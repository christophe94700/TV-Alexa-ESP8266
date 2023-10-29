void Ir_Envoi_On(uint8_t device) {
    if (device == 1) {
        for (int i = 0; i < 5; i++) {
            
            uint64_t code  = (EEPROMReadlong(ADRESS_IR_10 + i * IR_Mots, 4));
            uint8_t proto = ((EEPROM.read(ADRESS_IR_10 + i * IR_Mots + 4))-1);
            uint8_t nbit = (EEPROM.read(ADRESS_IR_10 + i * IR_Mots + 5));
            uint8_t rep  = (EEPROM.read(ADRESS_IR_10 + i * IR_Mots  + 6));
            uint8_t cde  = (EEPROM.read(ADRESS_IR_10 + i * IR_Mots  + 7));
            Serial.println("Device 1 IRSend: ");
            if ((cde == 0)or (cde == 1))  {
                delay(200);
                for (int l = 0; l <= rep; l++) {
                    IRSendProto(proto,code,nbit);
                }
            }
        }
    }
    if (device == 2) {
        for (int i = 0; i < 5; i++) {
            uint64_t code  = (EEPROMReadlong(ADRESS_IR_20 + i * IR_Mots, 4));
            uint8_t proto = ((EEPROM.read(ADRESS_IR_20 + i * IR_Mots + 4))-1);
            uint8_t nbit = (EEPROM.read(ADRESS_IR_20 + i * IR_Mots + 5));
            uint8_t rep  = (EEPROM.read(ADRESS_IR_20 + i * IR_Mots  + 6));
            uint8_t cde  = (EEPROM.read(ADRESS_IR_20 + i * IR_Mots  + 7));
            Serial.println("Device 2 IRSend: ");
            if ((cde == 0)or (cde == 1)) {
                delay(200);
                for (int l = 0; l <= rep; l++) {
                    IRSendProto(proto,code,nbit);
                }
            }
        }
    }
    sendState(device,1);
}

void Ir_Envoi_Off(uint8_t device) {
    if (device == 1) {
        for (int i = 0; i < 5; i++) {
            
            uint64_t code  = (EEPROMReadlong(ADRESS_IR_10 + i * IR_Mots, 4));
            uint8_t proto = ((EEPROM.read(ADRESS_IR_10 + i * IR_Mots + 4))-1);
            uint8_t nbit = (EEPROM.read(ADRESS_IR_10 + i * IR_Mots + 5));
            uint8_t rep  = (EEPROM.read(ADRESS_IR_10 + i * IR_Mots  + 6));
            uint8_t cde  = (EEPROM.read(ADRESS_IR_10 + i * IR_Mots  + 7));
            Serial.println("Device 1 IRSend: ");
            if ((cde == 0)or (cde == 2))  {
                delay(200);
                for (int l = 0; l <= rep; l++) {
                    IRSendProto(proto,code,nbit);
                }
            }
        }
    }
    if (device == 2) {
        for (int i = 0; i < 5; i++) {
            uint64_t code  = (EEPROMReadlong(ADRESS_IR_20 + i * IR_Mots, 4));
            uint8_t proto = ((EEPROM.read(ADRESS_IR_20 + i * IR_Mots + 4))-1);
            uint8_t nbit = (EEPROM.read(ADRESS_IR_20 + i * IR_Mots + 5));
            uint8_t rep  = (EEPROM.read(ADRESS_IR_20 + i * IR_Mots  + 6));
            uint8_t cde  = (EEPROM.read(ADRESS_IR_20 + i * IR_Mots  + 7));
            Serial.println("Device 2 IRSend: ");
            if ((cde == 0)or (cde == 2)) {
                delay(200);
                for (int l = 0; l <= rep; l++) {
                    IRSendProto(proto,code,nbit);
                }
            }
        }
    }
    sendState(device,0);
}

void IRSendProto(uint8_t proto, uint64_t code, uint8_t nbit) {
    // Make the appropriate call for the protocol type.
    switch (proto) {
        delay(50);
        case NEC:
        irsend.sendNEC(code, nbit);
        break;
        
        case SAMSUNG:
        irsend.sendSAMSUNG(code, nbit);
        break;
        
        
        default:
        
        break;
    }
    
}


void dump(decode_results *results) {
    // Dumps out the decode_results structure.
    // Call this after IRrecv::decode()
    uint16_t count = results->rawlen;
    
    
    if ((results->decode_type == UNKNOWN) or (results->bits == 0) ) {
        return;
        } else {
        Serial.print("Decodage ");
        Serial.print(pointer[(results->decode_type) + 1]);
        Serial.print(":");
        IrCode = (pointer[(results->decode_type) + 1]);
        IrCode = IrCode + " ";
    }
    
    unsigned long long1 = (unsigned long)(((results->value) & 0xFFFF0000) >> 16 );
    unsigned long long2 = (unsigned long)(((results->value) & 0x0000FFFF));
    
    String hex = String(long1, HEX) + String(long2, HEX); // six octets
    hex.toUpperCase();
    
    Serial.print(hex);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(" bits)");
    IrCode = IrCode + "Code: 0x" + hex + " Bit: " + String(results->bits, DEC);
    
}

void Active_IrCode(String ParaIr) {
    // Lecture des paramètres
    StringSplitter *splitter = new StringSplitter(ParaIr, ',', Nbrs_Para_IR);  // Initialisation de la classe avec x paramètres
    int itemCount = splitter->getItemCount();
    String para[itemCount];
    Serial.print("Paramètres IR :");
    for (int i = 0; i < itemCount; i++) {
        String item = splitter->getItemAtIndex(i);
        Serial.println("Valeur " + String(i) + ": " + (item) + " ");
        para[i] = item;
    }
    int NumIr = (para[0]).toInt() - 10;
    if (NumIr > 4) NumIr = NumIr - 5;
    uint32_t tmp  = (uint32_t) strtol(para[1].c_str(), NULL, 16);
    Serial.print("Code: ");
    Serial.print(String(tmp));
    EEPROMWritelong(ADRESS_IR_10 + NumIr * IR_Mots, tmp, 4); // Sauvegarde du code ID 32 Bits
    Serial.print("Pro: ");
    Serial.print(String(ValPro(para[2])));
    Serial.print("Nbit: ");
    Serial.print(String(para[3]).toInt());
    Serial.print(" Rep: ");
    Serial.println(String(para[4]).toInt());
    Serial.print(" Mode: ");
    Serial.println(String(para[5]).toInt());
    EEPROM.write(ADRESS_IR_10 + 4 + NumIr * IR_Mots, (ValPro(para[2])));
    EEPROM.write(ADRESS_IR_10 + 5 + NumIr * IR_Mots, (para[3]).toInt());
    EEPROM.write(ADRESS_IR_10 + 6 + NumIr * IR_Mots, (para[4]).toInt());
    EEPROM.write(ADRESS_IR_10 + 7 + NumIr * IR_Mots, (para[5]).toInt());
    EEPROM.commit();
}

// Renvois le nombre du protocole
int ValPro(String valeur) {
    for (int i = 0; i < 54; i++) {
        //Serial.println(pointer[i]);
        if (valeur == (pointer[i])) {
            return i;
        }
    }
 // Gérer d'autres cas ou valeurs si nécessaire.
    return 0; // Valeur par défaut si nbit n'est ni 4 ni 2.
}

String EtatIr(uint8_t Ir) {
    String texte;
    texte = "Dev: " + String(Ir) + "</BR>";
    for (int l = 0; l < 5; l++) {
        texte = texte + " IR: " + String(l);
        texte = texte + " Code : " + String(EEPROMReadlong(ADRESS_IR_10 + l * IR_Mots + Ir * IR_Mots * 5, 4), HEX);
        texte = texte + " Prot : " + String(EEPROM.read(ADRESS_IR_10 + l * IR_Mots + Ir * IR_Mots * 5 + 4));
        texte = texte + " Nbit : " + String(EEPROM.read(ADRESS_IR_10 + l * IR_Mots + Ir * IR_Mots * 5 + 5));
        texte = texte + " Rep : " + String(EEPROM.read(ADRESS_IR_10 + l * IR_Mots + Ir * IR_Mots * 5 + 6));
        texte = texte + " Mode : " + String(EEPROM.read(ADRESS_IR_10 + l * IR_Mots + Ir * IR_Mots * 5 + 7)) + "</BR>";
        
    }
    return texte;
}
