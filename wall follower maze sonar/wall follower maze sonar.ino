     
//Motor A
int enableA = 6;
int MotorA1 = 8;
int MotorA2 = 7;
 
//Motor B
int enableB = 3;
int MotorB1 = 2;
int MotorB2 = 4;


#define trigPin 13
#define echoPin 12

void setup() {
  
  //Serial.begin (9600);
  //configure pin modes
  pinMode (enableA, OUTPUT);
  pinMode (MotorA1, OUTPUT);
  pinMode (MotorA2, OUTPUT);  
  
  pinMode (enableB, OUTPUT);
  pinMode (MotorB1, OUTPUT);
  pinMode (MotorB2, OUTPUT); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

}

void stop()
{
    digitalWrite (MotorA1, LOW);
    digitalWrite (MotorB1, LOW);
    
    digitalWrite (MotorA2, LOW);
    digitalWrite (MotorB2, LOW);
}

void goLeft()
{
    digitalWrite (MotorA1, LOW);
    digitalWrite (MotorB1, LOW);
    digitalWrite (MotorA2, LOW);
    digitalWrite (MotorB2, HIGH);      
}

void turnLeft()
{
    digitalWrite (MotorA1, HIGH);
    digitalWrite (MotorB1, LOW);
    digitalWrite (MotorA2, LOW);
    digitalWrite (MotorB2, HIGH);
}

void goRight()
{
    digitalWrite (MotorA1, LOW);
    digitalWrite (MotorB1, LOW);
    digitalWrite (MotorA2, HIGH);
    digitalWrite (MotorB2, LOW);
    
}
void turnRight()
{
    digitalWrite (MotorA1, LOW);
    digitalWrite (MotorB1, HIGH);
    digitalWrite (MotorA2, HIGH);
    digitalWrite (MotorB2, LOW);
}

void goFront()
{
    digitalWrite (MotorA1, LOW);
    digitalWrite (MotorB1, LOW);
    digitalWrite (MotorA2, HIGH);
    digitalWrite (MotorB2, HIGH);
}

void goBack()
{
    digitalWrite (MotorA1, HIGH);
    digitalWrite (MotorB1, HIGH);
    digitalWrite (MotorA2, LOW);
    digitalWrite (MotorB2, LOW);
}




void loop() {
  
  analogWrite (enableA, 190);
  analogWrite (enableB, 190);
  Serial.println(echoPin);
  //goFront();


  //lets try this
   long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 40) {  // This is where the LED On/Off happens
    turnRight();
    //delay(500);
  }
  else {
    goFront();
  }
  
  //print statement
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  
}
