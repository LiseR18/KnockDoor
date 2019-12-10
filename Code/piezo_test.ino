const int piezo = A0;
const int led = 2;
int threshold = 100;

void setup() {
  Serial.begin(9600);
  pinMode(piezo, INPUT);
  pinMode(led, OUTPUT);

  //test led
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
}

void loop() {
  int piezo_val = analogRead(piezo);
  Serial.println(piezo_val);
  if (piezo_val >= threshold) {
    digitalWrite(led, LOW);
  } else {
    digitalWrite(led, HIGH);
  }
}
