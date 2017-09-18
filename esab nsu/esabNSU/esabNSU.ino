
 
int rightBaseSpeed =120 ;// this is the speed at which the motors should spin when the robot is perfectly on the line
int leftBaseSpeed  =120; // this is the speed at which the motors should spin when the robot is perfectly on the line
#define NUM_SENSORS  8     // number of sensors used
#define timegap   10
int base =150;
int senval[8];
bool checkflag =false;
char arr[100];
int numsen =0;
int position=0;
char lastpos ='n';
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
  pinMode(9,OUTPUT);
  pinMode(12,INPUT);
  pinMode(A0, INPUT);pinMode(A1, INPUT);pinMode(A2, INPUT);pinMode(A3, INPUT);
  pinMode(A4, INPUT);pinMode(A5, INPUT);pinMode(8, INPUT);pinMode(7, INPUT);  
} 
bool online(int x)
{
  if(x==1)return true;
  return false;
}
int readline()
{
  
  senval[0]=digitalRead(A0); senval[1]=digitalRead(A1);senval[2]=digitalRead(A2);senval[3]=digitalRead(A3);
  senval[4]=digitalRead(A4); senval[5]=digitalRead(A5);senval[6]=digitalRead(7);senval[7]=digitalRead(8);
  numsen=0;
  int total=0;
  for(int i=0; i<8;i++)
  {
    if(senval[i]==1){total=total+((i+1)*10);numsen++;}
  }
  //Serial.print("total");Serial.println(total);
  if(numsen==0){return 0;}
  return (total/numsen);
  return 0;
}
void autoBalance()
{
  if(position ==45){leftBaseSpeed=base;rightBaseSpeed=base;moveforward();}
  else if (position >0 && position<=20){lastpos ='l';rotateleft();leftBaseSpeed =base; rightBaseSpeed =base; }
  else if(position >20&& position<=30){lastpos ='l';moveforward();leftBaseSpeed=base-90;rightBaseSpeed=base;}
  else if(position >30&& position<45){lastpos ='l';moveforward();leftBaseSpeed=base;rightBaseSpeed=base;}
  
  else if(position >45&& position<=60){lastpos ='r';moveforward();leftBaseSpeed=base;rightBaseSpeed=base;}
  else if(position >60&& position<=70){lastpos ='r';moveforward();leftBaseSpeed=base;rightBaseSpeed=base-90;}
  else if(position >70&& position<=80){lastpos ='r';rotateright();leftBaseSpeed=base;rightBaseSpeed=base;}
  else if(position==0)
  { 
    //leftBaseSpeed =base; rightBaseSpeed =base;
    if(lastpos=='l'){leftBaseSpeed =base+30; rightBaseSpeed =base-30;rotateleft();}
    else if(lastpos=='r'){leftBaseSpeed=base-30;rightBaseSpeed=base+30;rotateright();}
  }
}
/*void readsensors()
{ 
  senval[0]=digitalRead(A0);  senval[1]=digitalRead(A1);  senval[2]=digitalRead(A2);senval[3]=digitalRead(A3);  senval[4]=digitalRead(A4);  senval[5]=digitalRead(A5);
  senval[6]=digitalRead(9);  senval[7]=digitalRead(8);    
  for(int i=0;i<8;i++){Serial.print(senval[i]);}
  Serial.println("");
}*/
bool onisection()
{
  if(numsen>3){return true;}
  return false;
}
/*

bool leftroad()
{
  if()
}
bool rightroad()
{
  if(online(senval[4])&&online(senval[5])&&online(senval[6])&&online(senval[7])){return true;}
  return false;
}
bool straight()
{
  delay(timegap);
  readsensors();
  if(online(senval[3])||online(senval[4])){/*digitalWrite(13,HIGH);return true;}
  return false; 
}
bool noroad()
{
  if(!online(senval[3])&&!online(senval[4])&&!online(senval[0])&& !online(senval[1])&&!online(senval[2])&& ! online(senval[5])&&!online(senval[6])&& !online(senval[7])){Serial.print("noooooooooooooooooo reaaaaaad");
  return true;}
  return false;
}
void printval()
{
  
}*/
bool checkpoint()
{
  if(numsen>3&&!digitalRead(12)){return true;}
  return false;
}
void loop()
{   
  //readsensors();
  int x=0;
  while(true){
    
    position=readline();
    Serial.println(position);
    if(checkpoint()){break;} 
    if(onisection())
    {
     if(position<40||numsen==8)
      {
        digitalWrite(13,HIGH);
        leftBaseSpeed=base-40;rightBaseSpeed=base-40;
        while(digitalRead(A0)){moveforward();}
        
        leftBaseSpeed=base+30;rightBaseSpeed=base-50;
         while(digitalRead(A1)){rotateleft();}
         while(digitalRead(A2)){rotateleft();}
         while(digitalRead(A3)){rotateleft();}
         while(!digitalRead(A3)){rotateleft();}
         while(digitalRead(A5)){rotateleft();}
         
         while(digitalRead(7)){rotateleft();}
         while(digitalRead(8)){rotateleft();}
         rotateright();delay(100);
         digitalWrite(13,LOW);
         //arr[x]='l'; x++;
      }
     else if(position>50)
      {
        digitalWrite(9,HIGH);
        leftBaseSpeed=base-30;rightBaseSpeed=base-30;
        do{moveforward();}while(digitalRead(8));
        if(digitalRead(A3)||digitalRead(A4))
        {
          moveforward();
        }
        else if (!digitalRead(A3)&&!digitalRead(A4))
        {
          movebackward();delay(100);
          //rotateright();delay(200);
          leftBaseSpeed=base-20;rightBaseSpeed=base+30;
          do{rotateright();}while(!digitalRead(A3));
          rotateleft();delay(100); 
        }
        digitalWrite(9,LOW);
      }
     else {leftBaseSpeed=base-30;rightBaseSpeed=base-30;rotateleft(); }
    }
    else if(position==0)
    {
      digitalWrite(9,HIGH);digitalWrite(13,HIGH);
      //leftBaseSpeed=base-30;rightBaseSpeed=base-30;
      //movebackward();delay(20);
      if(lastpos=='l'){do{leftBaseSpeed =base+30; rightBaseSpeed =base-30;rotateleft();}while(!digitalRead(A3));rotateright();delay(100);}
      else if(lastpos=='r'){do{leftBaseSpeed=base-40;rightBaseSpeed=base+30;rotateright();}while(!digitalRead(A4));rotateleft();delay(100);}
      digitalWrite(9,LOW);digitalWrite(13,LOW);
    }
    
    //Serial.println(position);
      
    /*if(noroad())
    {
       do{readsensors();rotateright();}while(!online(senval[5])); arr[x]='b'; x++;
    }
    else if(!onisection()){ autoBalance(); }
    else if(onisection())
    {
      nomove();delay(5000);
      leftBaseSpeed=base-10; rightBaseSpeed=base-10;
      // movebackward();delay(200);
       if(leftroad())
       { //moveforward();delay(timegap);
         Serial.println("IN Left");
         
       }
       else 
       { 
         //moveforward(); delay(timegap);
         //do{ moveforward(); }while(online(senval[7])); 
         Serial.println("NOt Left");
         readsensors();
         if(online(senval[3])||online(senval[4])){moveforward(); arr[x]='s';x++;}
         else if(!online(senval[3]&&!online(senval[4])))
         { do{readsensors();rotateright();}while(!online(senval[4])); arr[x]='r';x++;}  
       }   
    }
     
   }*/
  autoBalance();
  }
  nomove();delay(3000);
  /* moveforward();delay(5000);
   movebackward();delay(5000);
   rotateleft();delay(5000);
   rotateright();delay(5000);
  */
  
}


