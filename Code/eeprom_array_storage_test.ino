#include <EEPROM.h>


int in[10] = {234, 1203, 560, 0, 0, 0, 0, 0, 0, 0};
int out[10] = {};

void setup() {
  Serial.begin(9600);
  int adress = 0;
  
  //Write
  /*
  for (int i = 0; i < 10; i++) {
    EEPROM.put(adress, in[i]);
    adress += 2;
  }
  */

 
  for (int j = 0; j < 10; j++) {
    EEPROM.get(adress, out[j]);
    adress += 2;
    Serial.println(out[j]);
  }
  
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
