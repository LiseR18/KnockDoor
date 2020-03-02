/*
 * Fichier principal, noyau de Knocki, ce fichier contient l'algorithme
 * principal du cycle de vie du programme.
 */

#include <EEPROM.h>
#include <Servo.h>

#include <ir_Lego_PF_BitStreamEncoder.h>
#include <boarddefs.h>
#include <IRremoteInt.h>
#include <IRremote.h>

// = = = = = Pattern = = = = = 
const int MAX_KNOCK = 10;
const int KNOCK_TOLERANCE = 100;
boolean recording = false;

//tableau dynamique qui se rempli dès que l'on écoute une combinaison
int dynamicPattern[MAX_KNOCK] = {}; 

//tableau contenant la combinaison secrète, 
//ne change pas sauf si l'utilisateur la met à jour
int savedPattern[MAX_KNOCK] = {}; 
int knockCount = 0;
unsigned long refTime;
unsigned long knockTime;


// = = = = = Piezo = = = = = 
const int PIEZO = A0;
const int THRESHOLD = 100; //sensibilité du capteur piezo
const int BOUNCE_DELAY = 150; //délai anti-rebond

// = = = = = LEDs = = = = = 
const byte RED = 2;
const byte BLUE = 3;
const byte GREEN = 4;
const byte YELLOW = 5;
const byte WHITE = 6;

// = = = = = Buzzer = = = = = 
const int BUZZER = 7;

// = = = = = Servomotor = = = = = 
const int SERVO = 9;

// = = = = = IR Receiver = = = = =
const int IR = 11;
IRrecv irrecv(IR);
decode_results results;

// = = = = = = = = = = = = = = =
// = = = = = Programme = = = = = 
// = = = = = = = = = = = = = = =

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  ledSetup();
  lockSetup();
  retrievePatternFromMemory();
}

void loop() {
  
  //commandes de la télécommande
  if (irrecv.decode(&results)) {
    irrecv.resume();
    Serial.println(results.value);
    switch (results.value) {
      case 16724175: //bouton 1
        openLock();
        break;
      case 16718055: //bouton 2
        closeLock();
        break;
      case 16743045: //bouton 3
        if (!recording) {
          turnOnLed(YELLOW);
          recording = true;
        } else {
          turnOffLed(YELLOW);
          recording = false;
        }
        break;
      case 16712445: //bouton play/pause
        showPattern();
        break;
      default:
        Serial.println("Touche inconnue");
        break;
    }
  }

  listenToPattern();
}
