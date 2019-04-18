const int pin = 2;
const int speed1 = 1000;
const int speed2 = 100;
const int speed3 = 10;
const int speed4 = 5;
const int speed5 = 1;
const int burstSep = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
  hex("Sicko Mode");

  String bitSickoMode = "1010011110100111000111101011110111101000001001101110111111001001100101";
  readBinaryString(bitSickoMode);
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
  Serial.print("\n");
  Serial.println("starting message with 5 pulses");
  burst(5);
}

String decToBinary(int n) {
    // returns a binary string representing an english letter
    String binaryString = "";
    for (int i = 6; i >= 0; i--) {
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

void hex(String s) {
  int stringLength = s.length() + 1;
  char charArr[stringLength];
  strcpy(charArr, s.c_str());  // character array of our message string
  String binaryArray[stringLength];  // will store binary strings for each character
  int messageLength = 0;

  // turn character array into array of bit strings
  for(int i = 0; i < stringLength-1; i++){
    int intCast = int(charArr[i]);
    String binaryString = decToBinary(intCast);
//    Serial.print("\n");
//    Serial.print(charArr[i]);
//    Serial.print(" ");
//    Serial.print(binaryString);
    binaryArray[i] = binaryString;
    messageLength += binaryString.length();
  }
  
  // message now converted to a list of binary representations of letters
  // now send binary sequences to laser
  startMessage();
  Serial.println("now beginning message transmission");
  Serial.print("total message is "); 
  Serial.print(messageLength); Serial.println(" pulses");

  // send our bit strings
  for(int i = 0; i < stringLength - 1; i++){
    Serial.println(charArr[i]);
    Serial.println(int(charArr[i]));
    sendBinary(binaryArray[i], speed4);
  }
}

void sendBinary(String binary, int speed) {
//  delay(1000);
  for (int i=0; i < binary.length(); i++) {
    Serial.print(binary.charAt(i));
    if (binary.charAt(i) == '1') {
      pulse(speed, speed);
    }
    else if (binary.charAt(i) == '0') {
      emptyPulse(speed, speed);
    }
  }
  Serial.print("\n");
}

int binaryPower(int power) {
  int number = 1;
  for(int i=0; i < power; i++) {
    number = number * 2;
  }
  return number
}

void readBinaryString(String binaryString) {
  // assumes that 5 pulse message start indicator not present
  int messageLength = binaryString.length() + 1;
  char bitArr[messageLength];
  strcpy(bitArr, binaryString.c_str());
  char receivedCharArray[((messageLength-1)/7)+1];

  // begin decoding of our converted bit array
  for(int i=0; i < messageLength; i+=7) {
    
    int sum = 0;
    for(int j=0; j < 7; j++) {
      Serial.print(bitArr[i+j]);
      if (bitArr[i+j] == '1') {
        sum += binaryPower(6 - j);
      }
    }
    Serial.print(" "); Serial.print(sum);
    char character = char(sum);
    Serial.print(" "); Serial.println(character);
  }
}
