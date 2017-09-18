
//Motor A
int enableA = 6;
int MotorA1 = 7;
int MotorA2 = 8;
 
//Motor B
int enableB = 3;
int MotorB1 = 2;
int MotorB2 = 4;


//sensor
int s1 = A0;
int s2 = A1;
int s3 = A2;
int s4 = A3;

 
void setup() {
  
  Serial.begin (9600);
  //configure pin modes
  pinMode (enableA, OUTPUT);
  pinMode (MotorA1, OUTPUT);
  pinMode (MotorA2, OUTPUT);  
  
  pinMode (enableB, OUTPUT);
  pinMode (MotorB1, OUTPUT);
  pinMode (MotorB2, OUTPUT); 
}


void loop() {
  
  if(digitalRead(s2)==1 && digitalRead(s3)==1 && digitalRead(s1)==0 && digitalRead(s4)==0)    //on black line
  {
    analogWrite (enableA, 255);
    analogWrite (enableB, 255);
    digitalWrite (MotorA1, LOW);
    digitalWrite (MotorB1, LOW);
    digitalWrite (MotorB2, HIGH);
    digitalWrite (MotorA2, HIGH);
  }else if(digitalRead(s2)==0 && digitalRead(s3)==1 && digitalRead(s1)==0 && digitalRead(s4)==0)  //move little left
  {
    analogWrite (enableA, 255);
    analogWrite (enableB, 255);
    digitalWrite (MotorA1, LOW);
    digitalWrite (MotorB1, LOW);
    digitalWrite (MotorB2, HIGH);
    digitalWrite (MotorA2, LOW);
  }else if(digitalRead(s2)==0 && digitalRead(s3)==1 && digitalRead(s1)==0 && digitalRead(s4)==1)  //move more left
  {
    analogWrite (enableA, 255);
    analogWrite (enableB, 255);
    digitalWrite (MotorA1, LOW);
    digitalWrite (MotorB1, LOW);
    digitalWrite (MotorB2, HIGH);
    digitalWrite (MotorA2, LOW);
  }else if(digitalRead(s2)==1 && digitalRead(s3)==0 && digitalRead(s1)==0 && digitalRead(s4)==0)  //move right
  {
    analogWrite (enableA, 255);
    analogWrite (enableB, 255);
    digitalWrite (MotorA1, LOW);
    digitalWrite (MotorB1, LOW);
    digitalWrite (MotorB2, LOW);
    digitalWrite (MotorA2, HIGH);
  }else if(digitalRead(s2)==1 && digitalRead(s3)==0 && digitalRead(s1)==1 && digitalRead(s4)==0)  //move more r8
  {
    analogWrite (enableA, 255);
    analogWrite (enableB, 255);
    digitalWrite (MotorA1, LOW);
    digitalWrite (MotorB1, LOW);
    digitalWrite (MotorB2, LOW);
    digitalWrite (MotorA2, HIGH);
  }else if(digitalRead(s2)==1 && digitalRead(s3)==1 && digitalRead(s1)==1 && digitalRead(s4)==0)  //move L shape R8
  {
    analogWrite (enableA, 255);
    analogWrite (enableB, 255);
    digitalWrite (MotorA1, LOW);
    digitalWrite (MotorB1, LOW);
    digitalWrite (MotorB2, LOW);
    digitalWrite (MotorA2, HIGH);
  }else if(digitalRead(s2)==1 && digitalRead(s3)==1 && digitalRead(s1)==0 && digitalRead(s4)==1)  //move L shape left
  {
    analogWrite (enableA, 255);
    analogWrite (enableB, 255);
    digitalWrite (MotorA1, LOW);
    digitalWrite (MotorB1, LOW);
    digitalWrite (MotorB2, HIGH);
    digitalWrite (MotorA2, LOW);
  }else if(digitalRead(s2)==0 && digitalRead(s3)==0 && digitalRead(s1)==0 && digitalRead(s4)==0)  //stop
  {
    analogWrite (enableA, 0);
    analogWrite (enableB, 0);
    
  }
}
