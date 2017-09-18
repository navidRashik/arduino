const int led=9;
const int button=2;

void setup() {
  // put your setup code here, to run once:
  pinMode (led, OUTPUT);
  pinMode (button, INPUT);

}

void loop() {
  if (digitalRead(button)==HIGH)
  {
    digitalWrite(led,HIGH);
  }
  else{
    digitalWrite(led,LOW);
  }

}
