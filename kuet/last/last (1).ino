     
//Motor left
int enableA = 10;
int MotorA1 = 3;
int MotorA2 = 2;
 
//Motor right
int enableB = 11;
int MotorB1 = 5;
int MotorB2 = 4;


//sensor
int s1 = A0;
int s2 = A1;
int s3 = A2;
int s4 = A3;
int s5 = A4;
int s6 = A5;
int s7 = 9;
int s8 = 8;

bool first=false;
bool secoend=false;
int handler=0;
int sensorValue[]={0,0,0,0,0,0,0,0};
void setup() {
  
  //Serial.begin (9600);
  //configure pin modes
  pinMode (enableA, OUTPUT);
  pinMode (MotorA1, OUTPUT);
  pinMode (MotorA2, OUTPUT);  
  
  pinMode (enableB, OUTPUT);
  pinMode (MotorB1, OUTPUT);
  pinMode (MotorB2, OUTPUT); 

  pinMode (s1, INPUT);
  pinMode (s2, INPUT);
  pinMode (s3, INPUT);
  pinMode (s4, INPUT);
  pinMode (s5, INPUT);
  pinMode (s6, INPUT);
  pinMode (s7, INPUT);
  pinMode (s8, INPUT);
  Serial.begin(9600);

}

void readSensors()
{
  sensorValue[0]=digitalRead(s1);
  sensorValue[1]=digitalRead(s2);
  sensorValue[2]=digitalRead(s3);
  sensorValue[3]=digitalRead(s4);
  sensorValue[4]=digitalRead(s5);
  sensorValue[5]=digitalRead(s6);
  sensorValue[6]=digitalRead(s7);
  sensorValue[7]=digitalRead(s8);
   
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
    //delay(10);      
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
    //delay(10);
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



void only_p()
{
    readSensors();
    float sum=0;
    float track=0;
    float avg=0;
    for(int i=0 ;i<8;i++)
    {
      sum=sum+(sensorValue[i]*10*(i+1));
      
      
      if(sensorValue[i]==1)
      {
        track++;
      }
    }
    if(track!=0)
    {
      avg=(sum/track);
    }else{
      avg=0;
    }
    
//    if(avg<42 && avg>40)
//    {
//      goRight();
//    }
//    else if(avg>48 && avg<50)
//    {
//      goLeft();
//    }
//
//  if(avg==270){
//    stop();
//  }
    if(avg==0 && first==true)
    {
      analogWrite (enableA, 40);
      analogWrite (enableB, 40);
      turnRight();
      //delay(50);
      //first==false;
      //Serial.println("r8" );
    }
    else if(avg==0 && secoend==true)
    {
//      analogWrite (enableA, 40);
//      analogWrite (enableB, 40);
      turnLeft();
      //delay(50);
      //Serial.println("left" );
    }
    else if(avg<=20 )
    {
//      analogWrite (enableA, 55);
//      analogWrite (enableB, 55);
      turnRight();
      first=true;
      secoend=false;
    }
   else if(avg<=42 )
    {
//      analogWrite (enableA, 50);
//      analogWrite (enableB, 50);
      goRight();
      first=true;
      secoend=false;
    }
    
    else if(avg>=67 )
    {
//      analogWrite (enableA, 55);
//      analogWrite (enableB, 55);
      turnLeft();
      first=false;
      secoend=true;
    }
    else if(avg>=47 )
    {
//      analogWrite (enableA, 50);
//      analogWrite (enableB, 50);
      goLeft();
      first=false;
      secoend=true;
    }
    else if(avg>42 && avg<47)
    {
      goFront();
      
    }
//     else if(avg<42 && avg>40)
//    {
//      goRight();
//    }
//    else if(avg>48 && avg<50)
//    {
//      goLeft();
//    }
    
    Serial.println(avg );
    
}

void loop() {
  
  analogWrite (enableA, 95);
  analogWrite (enableB, 95);
  //goFront();
  only_p();
  
 // goLeft();
  //goLeft();
  //digitalRead(s1);
}


