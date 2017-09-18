
#define rightMaxSpeed 100 // max speed of the robot
#define leftMaxSpeed 100 // max speed of the robot
int rightBaseSpeed =60 ;// this is the speed at which the motors should spin when the robot is perfectly on the line
int leftBaseSpeed  =60; // this is the speed at which the motors should spin when the robot is perfectly on the line
#define NUM_SENSORS  8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 us for sensor outputs to go low
#define timegap   10
int base =155;
int senval[8];
bool checkflag =false;
char arr[100];
#define rightMotor1 2
#define rightMotor2 3
#define rightMotorPWM 10
#define leftMotor1 4
#define leftMotor2 5
#define leftMotorPWM 11

#define moveforward();    analogWrite(leftMotorPWM,leftBaseSpeed);analogWrite(rightMotorPWM,rightBaseSpeed);digitalWrite(leftMotor1, HIGH); digitalWrite(leftMotor2, LOW); digitalWrite(rightMotor1, HIGH); digitalWrite(rightMotor2, LOW)
#define movebackward();   analogWrite(leftMotorPWM,leftBaseSpeed);analogWrite(rightMotorPWM,rightBaseSpeed);digitalWrite(leftMotor1, LOW); digitalWrite(leftMotor2, HIGH); digitalWrite(rightMotor1, LOW); digitalWrite(rightMotor2, HIGH)
#define rotateleft();     analogWrite(leftMotorPWM,leftBaseSpeed);analogWrite(rightMotorPWM,rightBaseSpeed);digitalWrite(leftMotor1, LOW); digitalWrite(leftMotor2, HIGH); digitalWrite(rightMotor1, HIGH); digitalWrite(rightMotor2, LOW)
#define rotateright();    analogWrite(leftMotorPWM,leftBaseSpeed);analogWrite(rightMotorPWM,rightBaseSpeed);digitalWrite(leftMotor1, HIGH); digitalWrite(leftMotor2, LOW); digitalWrite(rightMotor1, LOW); digitalWrite(rightMotor2, HIGH)
#define turnleft();       analogWrite(leftMotorPWM,leftBaseSpeed);analogWrite(rightMotorPWM,rightBaseSpeed);digitalWrite(leftMotor1, LOW); digitalWrite(leftMotor2, LOW); digitalWrite(rightMotor1, HIGH); digitalWrite(rightMotor2, LOW)
#define turnright();      analogWrite(leftMotorPWM,leftBaseSpeed);analogWrite(rightMotorPWM,rightBaseSpeed);digitalWrite(leftMotor1, HIGH); digitalWrite(leftMotor2, LOW); digitalWrite(rightMotor1, LOW); digitalWrite(rightMotor2, LOW)
#define revleft();        analogWrite(leftMotorPWM,leftBaseSpeed);analogWrite(rightMotorPWM,rightBaseSpeed);digitalWrite(leftMotor1, LOW); digitalWrite(leftMotor2, LOW); digitalWrite(rightMotor1, LOW); digitalWrite(rightMotor2, HIGH)
#define revright();       analogWrite(leftMotorPWM,leftBaseSpeed);analogWrite(rightMotorPWM,rightBaseSpeed);digitalWrite(leftMotor1, LOW); digitalWrite(leftMotor2, HIGH); digitalWrite(rightMotor1, LOW); digitalWrite(rightMotor2, LOW)
#define nomove();         analogWrite(leftMotorPWM,leftBaseSpeed);analogWrite(rightMotorPWM,rightBaseSpeed);digitalWrite(leftMotor1, LOW); digitalWrite(leftMotor2, LOW); digitalWrite(rightMotor1, LOW); digitalWrite(rightMotor2, LOW)


void setup()
{
  Serial.begin(9600);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);pinMode(A1, INPUT);pinMode(A2, INPUT);pinMode(A3, INPUT);
  pinMode(A4, INPUT);pinMode(A5, INPUT);pinMode(8, INPUT);pinMode(9, INPUT); 
 
}


//JOYETU VAI


bool online(int x)
{
  if(x==1)return true;
  return false;
}


void readsensors()
{ 
  senval[0]=digitalRead(A0);  senval[1]=digitalRead(A1);  senval[2]=digitalRead(A2);senval[3]=digitalRead(A3);  senval[4]=digitalRead(A4);  senval[5]=digitalRead(A5);
  senval[6]=digitalRead(9);  senval[7]=digitalRead(8);    
//  for(int i=0;i<8;i++){Serial.print(senval[i]);}
//  Serial.println("");
}

bool onisection()
{
  readsensors();
  if((online(senval[0])&&online(senval[1])&&online(senval[2]))||(online(senval[5])&&online(senval[6])&&online(senval[7]))||(online(senval[5])&&online(senval[6])&&online(senval[7])&&online(senval[0])&&online(senval[1])&&online(senval[2]))){return true;}
  return false;
}
bool leftroad()
{
  readsensors();
  if(online(senval[0])&&online(senval[1])&&online(senval[2])&&online(senval[3])){return true;}
  return false;
}
bool rightroad()
{
  readsensors();
  if(online(senval[4])&&online(senval[5])&&online(senval[6])&&online(senval[7])){return true;}
  return false;
}
bool straight()
{
  //delay(timegap);
  readsensors();
  if(online(senval[3])||online(senval[4])){/*digitalWrite(13,HIGH);*/return true;}
  return false; 
}
bool noroad()
{
  readsensors();
  if(!online(senval[0])&& !online(senval[1])&&!online(senval[2])&& !online(senval[3])&&!online(senval[4])&&! online(senval[5])&&!online(senval[6])&& !online(senval[7]))
  {
    Serial.print("noooooooooooooooooo reaaaaaad");
    return true;
  }
  return false;
}
void printval()
{
  
}
bool checkpoint()
{
  readsensors();
  if(online(senval[2])&&online(senval[3])&&online(senval[4])&&online(senval[5])&&!online(senval[0])&&!online(senval[7])){checkflag=true;}
  if(checkflag&&online(senval[0])&&online(senval[7])){return true;}
  if(!(online(senval[2])&&online(senval[3])&&online(senval[4])&&online(senval[5]))){checkflag=false;return false;}
  return false;
}





//NAVID PART

     
//Motor left
int enableA = rightMotorPWM;
int MotorA1 = rightMotor2;
int MotorA2 = rightMotor1;
 
//Motor right
int enableB = leftMotorPWM;
int MotorB1 = leftMotor2;
int MotorB2 = leftMotor1;


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



void autoBalance()
{
  
    readSensors();
    
    analogWrite (enableA, base);
    analogWrite (enableB, base);
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
    
    if(avg==0 && first==true)
    {
//      analogWrite (enableA, 40);
//      analogWrite (enableB, 40);
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
    Serial.println(avg );
    
}




void loop()
{   
  
  readsensors();
//  autoBalance();
  
  int x=0;
  while(!checkpoint())
  {   
    if(noroad())
    {
       do{readsensors();rotateright();}while(!online(senval[4])); arr[x]='b'; x++;
    }
    else if(!onisection()){ autoBalance(); }
    else if(onisection())
    {
       if(leftroad())
       { //moveforward();delay(timegap);
         Serial.println("IN Left");
         do{readsensors();rotateleft();}while(online(senval[3])||online(senval[4])); 
         do{readsensors();rotateleft();}while(!online(senval[3])); 
         arr[x]='l'; x++;
       }
       else if(!leftroad())
       { 
         //moveforward(); delay(timegap);
         do{ readsensors(); moveforward(); }while(online(senval[7])); 
         Serial.println("NOt Left");
         readsensors();
         if(online(senval[3])||online(senval[4])){moveforward(); arr[x]='s';x++;}
         else if(!online(senval[3]&&!online(senval[4])))
           { do{readsensors();rotateright();}while(!online(senval[4])); arr[x]='r';x++;}  
       }
       
     }
     
   }
   do{readsensors();rotateright();}while(online(senval[4]));
   do{readsensors();rotateright();}while(!online(senval[4])); 

   
}


