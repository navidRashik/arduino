#define echopin 7
#define trigpin 8
int time,distance;
void setup() {
  Serial.begin (9600);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  digitalWrite(trigpin,LOW);
  delay(2);
}

void loop() {
  
  digitalWrite(trigpin,HIGH);
  delay(2);
  digitalWrite(trigpin,LOW);
  time=pulseIn(echopin,HIGH);   //calculating time for receiving wave
  distance=time/58;         // converting time to distance in cm
  Serial.print(distance);
  Serial.print("cm \n");
  delay(1000);

}
