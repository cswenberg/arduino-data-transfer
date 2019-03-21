const int pin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  burst()
}

void burst() {
  pulse()
  pulse()
  pulse()
  digitalWrite(pin, LOW);
  delay(100);
}

void pulse() {
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
  delay(10);
}
