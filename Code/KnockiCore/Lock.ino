/*
 * Fichier contenant les fonctions utiles pour
 * interagir avec le verrou de la porte. 
 */

Servo servo;

void lockSetup() {
  Serial.println("Lock successfully initialized");
}

/*
 * Ouvre le verrou de la porte
 */
void openLock() {
  servo.attach(SERVO);
  servo.write(130);
  delay(500);
  servo.detach();
  blinkLed(GREEN, 300, 1);
}

/*
 * Ferme le verrou de la porte
 */
void closeLock() {
  servo.attach(SERVO);
  servo.write(80);
  delay(500);
  servo.detach();
  blinkLed(RED, 300, 1);
}
