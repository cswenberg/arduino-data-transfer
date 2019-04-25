const int pin = 2;
const int speed1 = 1000;
const int speed2 = 100;
const int speed3 = 10;
const int speed4 = 5;
const int speed5 = 1;
const float speed6 = 0.5;
const float speed7 = 0.1;
const int burstSep = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
//  String message = hex(randomBitString(10), speed4);
//  Serial.print("\n");
//  Serial.println(message);
  String s = randomBitString(500);
  startMessage(1.5);
  sendBinary(s, 1.5);
//  readBinaryString(message);
//  randomBitString(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  // pulse(speed2,speed2);
//  randomBitString(10);
}

String randomBitString(int length) {
  String s = "";
  for (int i = 0; i < length; i++) {
    int randomNum = int(random(2));
    if (randomNum) {
      s += "1";
    }
    else {
      s += "0";
    }
//    Serial.println(randomNum);
  }
  Serial.println(s);
  return s;
}

void upPulse(int t) {
  digitalWrite(pin, HIGH);
  delay(t);
}

void downPulse(int t) {
  digitalWrite(pin, LOW);
  delay(t);
}

void pulse(int t_high, int t_low) {
  upPulse(t_high);
  downPulse(t_low);
}

void emptyPulse(int t_high, int t_low) {
  digitalWrite(pin, LOW);
  delay(t_high);
  digitalWrite(pin, LOW);
  delay(t_low);
}

void burst(int number, int speed) {
  for (int i = 0; i < number; i++) {
    pulse(speed, speed);
  }
  digitalWrite(pin, LOW);
//  delay(burstSep);
}

void startMessage(int speed) {
  Serial.print("\n");
  Serial.println("starting message with 5 pulses");
  burst(30, speed);
}

String decToBinary(int n) {
    // returns a binary string representing an english letter
    String binaryString = "";
    for (int i = 7; i >= 0; i--) {
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

String hex(String s, int speed) {
  int stringLength = s.length() + 1;
  char charArr[stringLength];
  strcpy(charArr, s.c_str());  // character array of our message string
  String binaryArray[stringLength];  // will store binary strings for each character
  int messageLength = 0;
  String binaryMessage = "";
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
    binaryMessage += binaryString;
  }
  
  // message now converted to a list of binary representations of letters
  // now send binary sequences to laser
  startMessage(speed);
  Serial.println("now beginning message transmission");
  Serial.print("total message is "); 
  Serial.print(messageLength); Serial.println(" pulses");

  // send our bit strings
  for(int i = 0; i < stringLength - 1; i++){
    Serial.print(charArr[i]); Serial.print(" ");
//    Serial.println(int(charArr[i]));
    sendBinary(binaryArray[i], speed);
  }
  return binaryMessage;
}

void sendBinary(String binary, int speed) {
//  delay(1000);
  for (int i=0; i < binary.length(); i++) {
    Serial.print(binary.charAt(i));
    if (binary.charAt(i) == '1') {
//      pulse(speed, speed);
      upPulse(speed);
    }
    else if (binary.charAt(i) == '0') {
//      emptyPulse(speed, speed);
      downPulse(speed);
    }
  }
  Serial.print("\n");
}

int binaryPower(int power) {
  int number = 1;
  for(int i=0; i < power; i++) {
    number = number * 2;
  }
  return number;
}

void readBinaryString(String binaryString) {
  // assumes that 5 pulse message start indicator not present
  int messageLength = binaryString.length() + 1;
  char bitArr[messageLength];
  strcpy(bitArr, binaryString.c_str());
  char receivedCharArray[((messageLength-1)/8)+1];
  String message = "";
  // begin decoding of our converted bit array
  for(int i=0; i < messageLength; i+=8) {
    
    int sum = 0;
    for(int j=0; j < 8; j++) {
//      Serial.print(bitArr[i+j]);
      if (bitArr[i+j] == '1') {
        sum += binaryPower(7 - j);
      }
    }
//    Serial.print(" "); Serial.print(sum);
    char character = char(sum);
    message += character;
//    Serial.print(" "); Serial.println(character);
  }
  Serial.println("Final message is:"); Serial.println(message);
}
