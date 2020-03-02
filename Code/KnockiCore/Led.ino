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

  //Montre que toutes les LEDs fonctionnent
  turnOffLed(BLUE);
  turnOffLed(GREEN);
  turnOffLed(WHITE);
  turnOffLed(YELLOW);
  turnOffLed(RED);

  int blinkTime = 100;
  
  blinkLed(BLUE, blinkTime);
  blinkLed(GREEN, blinkTime);
  blinkLed(WHITE, blinkTime);
  blinkLed(YELLOW, blinkTime);
  blinkLed(RED, blinkTime);
  blinkLed(YELLOW, blinkTime);
  blinkLed(WHITE, blinkTime);
  blinkLed(GREEN, blinkTime);
  blinkLed(BLUE, blinkTime);
  
  turnOnLed(BLUE);
  turnOnLed(GREEN);
  turnOnLed(WHITE);
  turnOnLed(YELLOW);
  turnOnLed(RED);
  
  delay(200);
  
  turnOffLed(BLUE);
  turnOffLed(GREEN);
  turnOffLed(WHITE);
  turnOffLed(YELLOW);
  turnOffLed(RED);
}

void turnOnLed(byte color) {
  digitalWrite(color, LOW);
}

void turnOffLed(byte color) {
  digitalWrite(color, HIGH);
}

void blinkLed(byte color, int timeDelay) {
  digitalWrite(color, LOW);
  delay(timeDelay);
  digitalWrite(color, HIGH);
}

void blinkLed(byte color, int timeDelay, int iterations) {
  for (int i = 0; i < iterations; i++) {
    blinkLed(color, timeDelay);
    delay(timeDelay);
  }
}
