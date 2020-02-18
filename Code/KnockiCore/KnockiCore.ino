/*
 * Fichier principal, noyau de Knocki, ce fichier contient l'algorithme
 * principal du cycle de vie du programme.
 */

#include <Servo.h>

#include <ir_Lego_PF_BitStreamEncoder.h>
#include <boarddefs.h>
#include <IRremoteInt.h>
#include <IRremote.h>

// = = = = = Pattern = = = = = 
const int MAX_KNOCK = 10;
//tableau dynamique qui se rempli dès que l'on écoute une combinaison
int dynamicPattern[MAX_KNOCK] = {}; 
//tableau contenant la combinaison secrète, 
//ne change pas sauf si l'utilisateur la met à jour
int savedPattern[MAX_KNOCK] = {}; 

// = = = = = Piezo = = = = = 
const int PIEZO = A0;
const int THRESHOLD = 100; //sensibilité du capteur piezo
const int BOUNCE_DELAY = 150; //délai anti-rebond

// = = = = = LEDs = = = = = 
const int RED = 2;
const int BLUE = 3;
const int GREEN = 4;
const int YELLOW = 5;
const int WHITE = 6;

// = = = = = Buzzer = = = = = 
const int BUZZER = 7;

// = = = = = Servomotor = = = = = 
const int SERVO = 9;

// = = = = = IR Receiver = = = = =
const int IR = 11;
IRrecv irrecv(IR);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
//  buzzerSetup();
  ledSetup();
  lockSetup();
  //turnOffLed(RED);
  //turnOffLed(BLUE);
  //turnOffLed(GREEN);
  //turnOffLed(YELLOW);
  //turnOffLed(WHITE);
}

void loop() {
  /*
  blinkLed(RED, 100);
  blinkLed(YELLOW, 100);
  blinkLed(WHITE, 100);
  blinkLed(GREEN, 100);
  blinkLed(BLUE, 100);
  */
  //Ouverture/fermeture de la porte avec télécommanbde
  if (irrecv.decode(&results)) {
    irrecv.resume();
    if (results.value==16724175) {
      openLock();
      turnOnLed(WHITE);
    }
    if (results.value==16718055) {
      closeLock();
    }
  }

  if (analogRead(PIEZO) >= THRESHOLD) {
    Serial.println(analogRead(PIEZO));
    blinkLed(WHITE, 50);
    delay(150);
  }
}
