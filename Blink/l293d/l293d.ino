//Testing the DC Motors with
// L293D
 
//Define Pins
//Motor A
int enableA = 6;
int MotorA1 = 7;
int MotorA2 = 8;
 
//Motor B
int enableB = 3;
int MotorB1 = 4;
int MotorB2 = 2;
 
void setup() {
  
  Serial.begin (9600);
  //configure pin modes
  pinMode (enableA, OUTPUT);
  pinMode (MotorA1, OUTPUT);
  pinMode (MotorA2, OUTPUT);  
  
  pinMode (enableB, OUTPUT);
  pinMode (MotorB1, OUTPUT);
  pinMode (MotorB2, OUTPUT); 
  delay (3000); 
  
}
 
void loop() {
  //enabling motor A
  Serial.println ("Enabling Motors");
  analogWrite (enableA, 255);
  analogWrite (enableB, 255);
  
  //do something
 
  Serial.println ("Motion Forward");
  digitalWrite (MotorA1, HIGH);
  digitalWrite (MotorA2, LOW);
  
  digitalWrite (MotorB1, HIGH);
  digitalWrite (MotorB2, LOW);
 
  
 
  //3s forward
  //delay (10000);
  
 
//  //reverse
//  digitalWrite (MotorA1,HIGH);
//  digitalWrite (MotorA2,LOW);  
//  
//  digitalWrite (MotorB1,HIGH);
//  digitalWrite (MotorB2,LOW);  
// 
//  //5s backwards
//  delay (5000);
// 
//  //stop
//  digitalWrite (enableA, 0);
//  digitalWrite (enableB, 0);
//  delay (1000);
}
