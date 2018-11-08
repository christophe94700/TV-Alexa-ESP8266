
void Ir_Envoi_On() {
  Serial.println("HIFI");
  irsend.sendSAMSUNG(0x8087887, 32);
  delay(50);
  irsend.sendSAMSUNG(0x8087887, 32);
  delay(50);
  irsend.sendSAMSUNG(0x8087887, 32);
  delay(200);
  Serial.println("BoxTV");
  irsend.sendNEC(0xFF9A65, 32);
  delay(50);
  irsend.sendNEC(0xFF9A65, 32);
  delay(50);
  irsend.sendNEC(0xFF9A65, 32);
}

void Ir_Envoi_Off() {
  Serial.println("HIFI");
  irsend.sendSAMSUNG(0x8087887, 32);
  delay(50);
  irsend.sendSAMSUNG(0x8087887, 32);
  delay(50);
  irsend.sendSAMSUNG(0x8087887, 32);
  delay(200);
  Serial.println("BoxTV");
  irsend.sendNEC(0xFF9A65, 32);
  delay(50);
  irsend.sendNEC(0xFF9A65, 32);
  delay(50);
  irsend.sendNEC(0xFF9A65, 32);
  delay(200);
  Serial.println("Video");
  irsend.sendNEC(0x61D650AF, 32);
  delay(50);
  irsend.sendNEC(0x61D650AF, 32);
  delay(50);
  irsend.sendNEC(0x61D650AF, 32);
}
void Ir_Envoi_vol(uint8_t vol) {
  Serial.println("HIFI Volume");
  for (int i = 0; i <= 40; i++) {
    irsend.sendSAMSUNG(0x8086897, 32);
    delay(100);
  }
  vol = ((vol / 255)) * 100;
  if (vol > 25) vol = 25;
  for (int i = 0; i <= vol; i++) {
  irsend.sendSAMSUNG(0x808C837, 32);
    delay(100);
  }
}
void Ir_Envoi_Off_HIFI(){
Serial.println("HIFI");
  irsend.sendSAMSUNG(0x8087887, 32);
  delay(50);
  irsend.sendSAMSUNG(0x8087887, 32);
  delay(50);
  irsend.sendSAMSUNG(0x8087887, 32);
  delay(200);
}
