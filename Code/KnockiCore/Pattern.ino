/*
 * Fichier contenant les fonctions utiles
 * pour manipuler les combinaisons (ecouter, 
 * sauvegarder, comparer...)
 */


/*
 * Ecoute et enregistre une combinaison dans le tableau dynamicPattern
 * pour que l'on puisse la traiter plus tard (comparaison/sauvegarde)
 */
void listenToPattern() {
  do {
    if (analogRead(PIEZO) >= THRESHOLD) { //si un coup est frappé
      knockTime = millis(); //on enregistre le moment où le coup est frappé
      if (knockCount < MAX_KNOCK) { //si on n'a pas atteint le nombre de coup max
        if (knockCount == 0) { //si c'est le premier coup
          clearPattern(dynamicPattern);
          turnOnLed(BLUE);
        } else { //sinon on ajoute l'écart au tableau dynamicPattern
          dynamicPattern[knockCount - 1] = knockTime - refTime;
        }
        //dans tous les cas :
        refTime = knockTime; //on met à jour le temps de référence
        blinkLed(WHITE, 50); //on allume la led blanche pour dire que le coup est pris en compte
        delay(150);//on annule le rebond
        knockCount += 1;//on incrémente notre compteur de coups
        
      } else { //si on tape trop de coups
        blinkLed(RED, 200, 3);
        Serial.print("knocktoun");
        Serial.println(knockCount);
      }
      delay(1);
    }
  } while (millis() - refTime <= 2000); //tant que l'on a pas attendu 4 sec

  if (knockCount != 0) {
    Serial.println("On est sortis de la boucle, voici la combinaison enregistrée :");
    knockCount = 0; //on rénitialise le compteur de coups
    printPattern(dynamicPattern); //on affiche la combinaison dans le moniteur série
    turnOffLed(BLUE);
    
    if (recording) { //si on est en mode "enregistrement"
      savePatternToMemory(); //on savegarde la combinaison dans la mémoire
      turnOffLed(YELLOW);
      recording = false;
    } else {
      if (patternsValid()) { //si la combinaison est juste
        openLock();
      } else {
        blinkLed(RED, 200, 6);
      }
    }
  }
}


/*
 * Vide un tableau
 */
void clearPattern(int pattern[]) {
  for (int i = 0; i < MAX_KNOCK; i++) {
    pattern[i] = 0;
  }
}


/*
 * Affiche un tableau dans le moniteur série
 */
void printPattern(int pattern[]) {
  for (int i = 0; i < MAX_KNOCK; i++) {
    Serial.println(pattern[i]);
  }
}

/*
 * Effecture une lecture de la mémoire EEPROM 
 * et remplit le tableau "savedPattern"
 * avec les valeurs lues dans la mémoire
 */
void retrievePatternFromMemory() {
  int address = 0;
  for (int i = 0; i < MAX_KNOCK; i++) {
    EEPROM.get(address, savedPattern[i]);
    address += 2;
  }
  Serial.println("Pattern récupéré de la mémoire :");
  printPattern(savedPattern);
}


/*
 * Copie les valeurs du tableau "dynamicPattern"
 * dans "savedPattern" et sauvegarde ce dernier
 * dans la mémoire EEPROM
 */
void savePatternToMemory() {
  int address = 0;
  for (int i = 0; i < MAX_KNOCK; i++) {
    savedPattern[i] = dynamicPattern[i];
    EEPROM.put(address, dynamicPattern[i]);
    address += 2;
  }
  Serial.println("Pattern sauvegardé dans la mémoire :");
  printPattern(savedPattern);
}

/*
 * Compare les tableaux "dynamicPattern"
 * et "savedPattern" pour voir s'ils sont 
 * égaux à une incertitude de temps près
 */
boolean patternsValid() {
  printPattern(dynamicPattern);
  printPattern(savedPattern);
  for (int i = 0; i < MAX_KNOCK; i++) {
    int dyn = dynamicPattern[i];
    int saved = savedPattern[i];
    if (!((dyn >= saved - KNOCK_TOLERANCE) && (dyn <= saved + KNOCK_TOLERANCE))) {
      return false;
    }
  }
  return true;
}

void showPattern() {
  for (int i = 0; i < MAX_KNOCK; i++) {
    blinkLed(WHITE, 50);
    delay(savedPattern[i]);
  }
}
