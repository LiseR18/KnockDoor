#include <Servo.h>

Servo servo;
const int pot = A0;

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  pinMode(pot, INPUT);
}

void loop() {
  int pot_val = analogRead(pot);
  Serial.print("pot_val = ");
  Serial.println(pot_val);

  int servo_val = map(pot_val, 0, 1023, 0, 180);
  Serial.print("servo_val = ");
  Serial.println(servo_val);
  servo.write(servo_val);
}
