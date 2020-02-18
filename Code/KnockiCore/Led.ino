/*
 * Fichier contenant toutes les fonctions utiles pour
 * effectuer des retours visuels à l'utilisateur avec
 * les LEDs de la porte.
 */

void ledSetup() {
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(WHITE, OUTPUT);
  Serial.println("LEDs successfully initialized");
}

void turnOnLed(byte color) {
  digitalWrite(color, LOW);
}

void turnOffLed(byte color) {
  digitalWrite(color, HIGH);
}

void blinkLed(byte color, int time_delay) {
  digitalWrite(color, LOW);
  delay(time_delay);
  digitalWrite(color, HIGH);
}
