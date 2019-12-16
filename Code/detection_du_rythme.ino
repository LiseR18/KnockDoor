/* Detecte le rythme des coups */

const int piezo =A0;
int threshold = 100;
const int knockFadeTime = 150; //intervalle de temps pendant lequel on écoute plus de coup apres un coup
const int knockComplete =1200;
const int maximumKnocks = 10; //maximun de coups que notre rythme peut comporter

int secretCode[maximumKnocks] = {100,100,100,0,0,0,0,0,0,0}; //code présent de base pour dévérouiller la porte
int knockRead[maximumKnocks]; //lecture des coup
int piezo_val=0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("le programme démarre");
  pinMode(piezo, INPUT);

}

void loop() {
  //on écoute les coup
  piezo_val = analogRead(piezo);
  Serial.println(piezo_val);
  if (piezo_val >= threshold) {
    Serial.println("knock starting");   

  int i = 0;
  for (i=0;i<maximumKnocks;i++){
    knockRead[i]=0;
    Serial.println(knockRead[i]);
  }
  
  int currentKnockNumber=0;               // Incrementer for the array.
  int startTime=millis();                 // Reference for when this knock started.
  int now=millis();

  delay(knockFadeTime);                                 //on attend avant d'écouter le prochain coup

    //on écoute le prochain coup
    piezo_val = analogRead(piezo);
    if (piezo_val >=threshold){                   //on a un autre coup
      now=millis();
      knockRead[currentKnockNumber] = now-startTime;
      currentKnockNumber ++;                             //on ajoute notre coup au compteur 
      startTime=now;          
      // on re initialise notre temps pour le prochain coup
      delay(knockFadeTime); 
    }  
  }    
}                 

   
 
