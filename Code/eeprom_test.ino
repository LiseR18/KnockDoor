#include <EEPROM.h>

int eeprom_readout[] = {};

void setup() {
  Serial.begin(9600);
  //Commenter et décommenter les lignes pour écrire ou lire la mémoire
  //writeInts();
  readInts();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void writeInts() {
  int addr = 0; //l'adresse de l'octet courant
  while (addr < EEPROM.length()) { //tant qu'il reste des octets à 
    int rand_val = random(0, 256);
    Serial.println(rand_val);
    EEPROM.write(addr, rand_val); //on écrit à l'adresse de l'octet un nombre entre 0 et 255
    addr += 1; //on passe à l'octet suivant
  }
}


void readInts() {
  int addr = 0; //l'adresse de l'octet courant
  while (addr < EEPROM.length()) { //tant qu'il reste des octets à lire
    int value = EEPROM.read(addr); //on lit l'octet à l'adresse actuelle
    Serial.println(value);
    eeprom_readout[addr] = value; //on ajoute cette valeur à notre tableau
    addr += 1; //on passe à l'octet suivant 
  }
}
