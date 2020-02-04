const int max_knock = 10;
int ref_combinaison[max_knock] = {543, 243, 435, 0, 0, 0, 0, 0, 0, 0};
int current_combinaison[max_knock] = {540, 270, 438, 0, 0, 0, 0, 0, 0, 0};
int tolerance = 60;


void setup() {
  Serial.begin(9600);
  String is_right = "Juste";
  for (int i = 0; i < max_knock; i ++) {
    int current = current_combinaison[i];
    int ref = ref_combinaison[i];
    if (!((current >= (ref - tolerance)) && (current <= (ref + tolerance)))) {
      is_right = "Fausse";
    }
  }
  Serial.println(is_right);
}

void loop() {
  
}
