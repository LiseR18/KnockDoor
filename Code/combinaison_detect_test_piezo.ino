const int piezo = A5;
unsigned long ref_time; //temps de référence
const int max_knock = 10;
int combinaison[max_knock] = {};
int piezo_threshold = 100;


void setup() {
  Serial.begin(9600);

  //remplir le tableau de 0
  for (int i = 0; i < max_knock; i++) {
    combinaison[i] = 0;
  }
  for (int j = 0; j < max_knock; j++) {
    Serial.println(combinaison[j]);
  }

  ref_time = millis(); //on initialise le temps de référence
}


void loop() {
  int knock_count = 0; //nombre de coups reçus
  do { 
    
    if (analogRead(piezo) >= piezo_threshold) { //si le piezo prend un coup
      unsigned long knock_time = millis();
      
      Serial.print("BOUTON appuyé à : ");
      Serial.println(knock_time);

      if (knock_count <= 11) {
      
        if (knock_count == 0) { //si c'est  le premier coup tapé
          ref_time = knock_time;
        } else {
          //on ajoute à notre tableau le temps entre les 2 coups
          combinaison[knock_count - 1] = knock_time - ref_time; 
          
          Serial.print("millis - ref_time = ");
          Serial.print(knock_time);
          Serial.print(" - ");
          Serial.print(ref_time);
          Serial.print(" = ");
          Serial.println(knock_time - ref_time);
        }

        Serial.print("COUP NUMERO : ");
        Serial.println(knock_count);
        
        delay(150); //on évite le rebond
        knock_count += 1; //on incrémente notre compteur de coups
        ref_time = knock_time;
        
      } else {
        Serial.println("On a dépassé le nombre de coup");
        break;
      }
      
    }

  } while (millis() - ref_time <= 4000); //tant que l'on n'attend pas plus de 2 secondes

  
  knock_count = 0; //on a terminé d'enregistrer la combinaison donc on reset le compteur de coups
  
  //on affiche la combinaison
  Serial.println("On est sortis de la boucle, voici la combinaison enregistrée :");
  for (int i = 0; i < max_knock; i++) {
    Serial.println(combinaison[i]);
  }
  
}
