#include <Servo.h>

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>


int RECV_PIN = 11; //On définit le pin 11
IRrecv irrecv(RECV_PIN);
decode_results results; //stockage des données reçues

Servo servo;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn(); // Initialisation de la réception 
  servo.attach(3);
}

void loop(){
  if (irrecv.decode(&results))
    {
     Serial.println(results.value, DEC); //On affiche le code en hexadecimal
     irrecv.resume(); // Reçoit la valeur suivante
    }
    if (results.value==16724175){
      servo.write(100);

    }
    if (results.value==16718055){
      servo.write(20);
    }

}
