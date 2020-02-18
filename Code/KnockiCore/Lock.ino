/*
 * Fichier contenant les fonctions utiles pour
 * interagir avec le verrou de la porte. 
 */

Servo servo;

void lockSetup() {
  Serial.println("Lock successfully initialized");
}

void openLock() {
  servo.attach(SERVO);
  servo.write(130);
  delay(500);
  servo.detach();
}

void closeLock() {
  servo.attach(SERVO);
  servo.write(80);
  delay(500);
  servo.detach();
}
