const int pin = 2;
const int t_high = 10;
const int t_low = 10;
const int burst_sep = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  // Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  burst(3);
}

void burst(int number) {
  for (int i = 0; i < number; i++) {
    pulse(t_high, t_low);
  }
  digitalWrite(pin, LOW);
  delay(burst_sep);
}

void pulse(int t_high, int t_low) {
  digitalWrite(pin, HIGH);
  delay(t_high);
  digitalWrite(pin, LOW);
  delay(t_low);
}

void textToBinary() {
  String myText = "Hello World";
  for(int i=0; i<myText.length(); i++){
    char myChar = myText.charAt(i);
    for(int i=7; i>=0; i--){
      byte bytes = bitRead(myChar,i);
      Serial.print(bytes, BIN);
    }
    Serial.println("");
  }
}
