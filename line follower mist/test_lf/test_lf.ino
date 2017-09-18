     
//Motor A
int enableA = 6;
int MotorA1 = 7;
int MotorA2 = 8;
 
//Motor B
int enableB = 3;
int MotorB1 = 2;
int MotorB2 = 4;


//sensor
int s1 = A3;
int s2 = A2;
int s3 = A1;
int s4 = A0;

bool frontGap=false;
int handler=0;
int sensorValue[4]={0,0,0,0};
void setup() {
  
  //Serial.begin (9600);
  //configure pin modes
  pinMode (enableA, OUTPUT);
  pinMode (MotorA1, OUTPUT);
  pinMode (MotorA2, OUTPUT);  
  
  pinMode (enableB, OUTPUT);
  pinMode (MotorB1, OUTPUT);
  pinMode (MotorB2, OUTPUT); 
  Serial.begin(9600);

}

void readSensors()
{
  sensorValue[0]=digitalRead(s1);
  sensorValue[1]=digitalRead(s2);
  sensorValue[2]=digitalRead(s3);
  sensorValue[3]=digitalRead(s4);
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

bool onLine()
{
  readSensors();
  if(digitalRead(s2)==1 && digitalRead(s3)==1 && digitalRead(s1)==0 && digitalRead(s4)==0){
      return true;
  }else{
  return false;
  }
}

void travel()
{
  readSensors();
  if(onLine())  
  {
    goFront();
    Serial.println("0110" );
  }else if(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==0)
  {
    goRight();
    
    Serial.println(" 0010" );
  }
  else if(sensorValue[0]==0 && sensorValue[1]==1 && sensorValue[2]==0 && sensorValue[3]==0)
  {
    goLeft();
    
    Serial.println("0100" );
  }
//  else if(sensorValue[0]==1 && sensorValue[1]==1 && sensorValue[2]==1 && sensorValue[3]==1)
//  {
//    goFront();
//    Serial.println("1111" );
//  }
  else if(sensorValue[0]==0 && sensorValue[1]==1 && sensorValue[2]==1 && sensorValue[3]==1)
  {
    Serial.println("0111" );
    while(!(sensorValue[0]==0 && sensorValue[1]==1 && sensorValue[2]==1 && sensorValue[3]==0))
    {
      //analogWrite (enableB, 217);
      readSensors();
      turnRight();
    }
  }
  else if(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==0 && sensorValue[3]==1)
  {
    Serial.println("0001" );
    while(!(sensorValue[0]==0 && sensorValue[1]==1 && sensorValue[2]==1 && sensorValue[3]==0))
    {
      readSensors();
      goRight();
    }
  }
  else if(sensorValue[0]==1 && sensorValue[1]==1 && sensorValue[2]==1 && sensorValue[3]==0)
  {
    Serial.println("1110" );
    while(!(sensorValue[0]==0 && sensorValue[1]==1 && sensorValue[2]==1 && sensorValue[3]==0))
    {
      readSensors();
      turnLeft();
    }
  }
  else if(sensorValue[0]==1 && sensorValue[1]==0 && sensorValue[2]==0 && sensorValue[3]==0)
  {
    Serial.println("1000" );
    while(!(sensorValue[0]==0 && sensorValue[1]==1 && sensorValue[2]==1 && sensorValue[3]==0))
    {
      readSensors();
      goLeft();
    }
  }
//  else if(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==0 && sensorValue[3]==0)
//  {
//    Serial.println("0000" );
//    goFront();
//    //delay(500);
////    if(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==0 && sensorValue[3]==0)
////    {
////      while(!onLine())
////      {
////        readSensors();
////        goBack();
////      }
////    }
//  }
//  else if(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==1)
//  {
//    while(sensorValue[0]!=0 && sensorValue[1]!=1 && sensorValue[2]!=1 && sensorValue[3]!=1)
//    {
//      readSensors();
//      goRight();
//    }
//    while(sensorValue[0]!=0 && sensorValue[1]!=1 && sensorValue[2]!=1 && sensorValue[3]!=1)
//    {
//       readSensors();
//      goRight();
//    }
//  }

}




void loop() {
  
  analogWrite (enableA, 170);
  analogWrite (enableB, 170);
  travel();
  //turnRight();
}
