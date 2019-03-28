const int pin = 2;
const int speed1 = 1000;
const int speed2 = 100;
const int speed3 = 10;
const int speed4 = 1;
const int burstSep = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
  ascii("Hello World");

}

void loop() {
  // put your main code here, to run repeatedly:
  // pulse(speed2,speed2);
}

void pulse(int t_high, int t_low) {
  digitalWrite(pin, HIGH);
  delay(t_high);
  digitalWrite(pin, LOW);
  delay(t_low);
}

void emptyPulse(int t_high, int t_low) {
  digitalWrite(pin, LOW);
  delay(t_high);
  digitalWrite(pin, LOW);
  delay(t_low);
}

void burst(int number) {
  for (int i = 0; i < number; i++) {
    pulse(speed3, speed3);
  }
  digitalWrite(pin, LOW);
  delay(burstSep);
}

void startMessage() {
  burst(5);
}

String decToBinary(int n) {
    String binaryString = "";
    for (int i = 31; i >= 0; i--) {
        int k = n >> i;
        if (k & 1) {
            binaryString += "1";
        }
        else {
            binaryString += "0";
        }
    }
    return binaryString;
}

void ascii(String s) {
  int len = s.length() + 1;
  char char_arr[len];
  strcpy(char_arr, s.c_str());
  String binaryArray[len];
  for(int i = 0; i < len-1; i++){
    int n = int(char_arr[i]);
    Serial.print("\n");
    Serial.print(char_arr[i]);
    Serial.print(" ");
    Serial.print(decToBinary(n));
    binaryArray[i] = decToBinary(n);
  }
  for(int i = 0; i < len-1; i++){
    sendBinary(binaryArray[i])
  }
}

void sendBinary(String binary) {
  startMessage();
  delay(1000);
  for (int i=0; i < binary.length(); i++) {
    Serial.print("\n");
    Serial.print(binary.charAt(i));
    if (binary.charAt(i) == '1') {
      pulse(speed2, speed2);
    }
    else if (binary.charAt(i) == '0') {
      emptyPulse(speed2, speed2);
    }
  }
  Serial.print("done with loop");
}
