const int button = 7;
unsigned long ref_time;
const int max_knock = 10;
int combinaison[max_knock] = {};


void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);

  //remplir le tableau de 0
  for (int i = 0; i < max_knock; i++) {
    combinaison[i] = 0;
  }
}

void loop() {
  unsigned long ref_time = millis(); //temps de référence
  int button_val = digitalRead(button); //valeur du pin du bouton 
  int knock_count = 0;
  do { 
    if (button_val == LOW) { //si le bouton est appuyé
      //on ajoute à notre tableau le temps entre les 2 coups
      combinaison[knock_count] = millis() - ref_time; 
      ref_time = millis(); //le nouveau temps de référence est le temps actuel
      Serial.println(knock_count);
      knock_count += 1; //on incrémente notre compteur de coups
    }
  } while (millis() - ref_time <= 2000); //tant que l'on n'attend pas plus de 2 secondes
  knock_count = 0; //on a terminé d'enregistrer la combinaison donc on reset le compteur de coups
  //on affiche la combinaison
  for (int i = 0; i < max_knock; i++) {
    Serial.println(combinaison[i]);
  }
}
