const int analogInPin1=A0, analogInPin2=A1, analogInPin3=A2, analogInPin4=A3, analogInPin5=A4, analogInPin6=A5;
int sensorValue[5]={0,0,0,0,0};
int leftMotor1=3, leftMotor2 =4, rightMotor1 =5, rightMotor2 =6 ,pLight =7 ,hLight =8;
int leftPwm =9,rightPwm =10;
int handler =610;

struct point
{
  bool planetPresent;
  int planetMark;
  int present,X,Y;
  int up,down,left,right;
};

void readSensors()
{
  sensorValue[0]=analogRead(analogInPin1);
  sensorValue[1]=analogRead(analogInPin2);
  sensorValue[2]=analogRead(analogInPin3);
  sensorValue[3]=analogRead(analogInPin4);
  sensorValue[4]=analogRead(analogInPin5);
}
void halt()
{
  digitalWrite(leftMotor1,LOW);digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,LOW);digitalWrite(rightMotor2,LOW);
}
void goLeft()
{
  digitalWrite(leftMotor1,LOW);digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,HIGH);digitalWrite(rightMotor2,LOW);
}
void goRight()
{
  digitalWrite(leftMotor1,HIGH);digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,LOW);digitalWrite(rightMotor2,LOW);
}
void goFront()
{
  digitalWrite(leftMotor1,HIGH);digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,HIGH);digitalWrite(rightMotor2,LOW);
}
void goBack()
{
  digitalWrite(leftMotor1,LOW);digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,LOW);digitalWrite(rightMotor2,HIGH);
}
void turnRight()
{
  digitalWrite(leftMotor1,HIGH);digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,LOW);digitalWrite(rightMotor2,HIGH);
}
void turnLeft()
{
  digitalWrite(leftMotor1,LOW);digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,HIGH);digitalWrite(rightMotor2,LOW);
}
void turnIRight()
{
  if(!onLine()){do{travel();}while(!onLine());}
  if(onLine()){do{turnRight();}while(onLine());}
  if(!onLine()){do{turnRight();}while(!onLine());}
}
void turnILeft()
{
  if(!onLine()){do{travel();}while(!onLine());}
  if(onLine()){do{turnLeft();}while(onLine());}
  if(!onLine()){do{turnLeft();}while(!onLine());}
}
bool onLine()
{
  readSensors();
  if(sensorValue[2]>handler ) return true;
  return false;
}
bool onIsection()
{
  
  readSensors();
  if(sensorValue[0]>handler &&sensorValue[4]>handler ) 
  {digitalWrite(pLight,HIGH);digitalWrite(hLight,LOW);return true;}
  digitalWrite(pLight,LOW);
  return false;
}
bool gotPlanetMark()
{
  readSensors();
  if(sensorValue[0]<handler &&sensorValue[1]>=handler &&sensorValue[2]>=handler &&sensorValue[3]>=handler &&sensorValue[4]<handler ) return true;
  return false;
}
bool gotHole()
{
  readSensors();
  if(sensorValue[0]>handler &&sensorValue[2]<handler &&sensorValue[4]>handler ) return true;
  return false;
}
void travel()
{
  readSensors();
  if(sensorValue[1]<handler && sensorValue[3]<handler)goFront();
  else if(sensorValue[1]>handler && sensorValue[3]<handler)goRight();
  else if(sensorValue[1]<handler && sensorValue[3]>handler)goLeft();
}
struct point vertex[8][8];
void setup()
{
  pinMode(leftMotor1,OUTPUT); pinMode(leftMotor2,OUTPUT); pinMode(rightMotor1,OUTPUT); pinMode(rightMotor2,OUTPUT);
  pinMode(leftPwm,OUTPUT); pinMode(rightPwm,OUTPUT);
  analogWrite(leftPwm,195); analogWrite(rightPwm,195);
  int i,j;
  Serial.begin(9600);
  for(i=0;i<8;i++)
  {
    for(j=0;j<8;j++)
    {
      
      vertex[i][j].present=1;
      vertex[i][j].X=i;
      vertex[i][j].Y=j;
      vertex[i][j].planetMark =0;
    }
  }
  
}
void loop()
{
  int i,j;
   for(i=0;i<7;i++)
   {
     /////// for uphill ////u///
     for(j=0;j<7;j++)
     {
       do
       {
         if(gotPlanetMark())
         {
           vertex[i][j+1].planetMark=1;
           if(vertex[i][j].planetMark==1){vertex[i][j].planetPresent=true;}
         }
         travel();
       }while(!onIsection());
       if(gotHole()){vertex[i][j].present=0;}
       while(onIsection()){goFront();Serial.write(i);Serial.write("<- X y -> ");Serial.write(j);}
     }
     /////// for upside cross ///////
     if(!onLine()){do{travel();}while(!onLine());}     //for turn
     
     if(onLine()){do{turnRight();}while(onLine());}
     if(!onLine()){do{turnRight();}while(!onLine());}
     do                                                                                                          //planet identifier
     {
       
       if(gotPlanetMark())
       {
         vertex[i+1][j].planetMark=1;
         if(vertex[i][j].planetMark==1){vertex[i][j].planetPresent=true;}
       }
       travel();
     }while(!onIsection());
     if(gotHole()){vertex[i+1][j].present=0;}
     while(onIsection()){goFront();};
     if(!onLine()){do{travel();}while(!onLine());}
     
     if(onLine()){do{turnRight();}while(onLine());}
     if(!onLine()){do{turnRight();}while(!onLine());}
     i++;
     ///// for down hill //////////
     for(j=7;j>0;j--)
     { 
       do
       {
         if(gotPlanetMark())
         {
           vertex[i][j-1].planetMark=1;
           if(vertex[i][j].planetMark==1){vertex[i][j].planetPresent=true;}
         }
         travel();
       }while(!onIsection());
       if(gotHole()){vertex[i][j-1].present=0;}
       while(onIsection()){goFront();};
     }
     if(i==7){continue;}
     
      ///////// downSide cross ////////////
     if(!onLine()){do{travel();}while(!onLine());}
     
     
     if(onLine()){do{turnLeft();}while(onLine());}
     if(!onLine()){do{turnLeft();}while(!onLine());}
     do
     {
       if(gotPlanetMark())
       {
         vertex[i+1][j].planetMark=1;
         if(vertex[i][j].planetMark==1){vertex[i][j].planetPresent=true;}
       }
       travel();
     }while(!onIsection());
     if(gotHole()){vertex[i+1][j].present=0;}
     while(onIsection()){goFront();};
     if(!onLine()){do{travel();}while(!onLine());}
     
     if(onLine()){do{turnLeft();}while(onLine());}
     if(!onLine()){do{turnLeft();}while(!onLine());}
   }
   
   ///  calculations here //
   
   //// calculations ends /////
   turnIRight();
   turnIRight();
   /// travel to (7,7) ///////
   for(i=0;i<7;i++)
   {
     do{travel();}while(!onIsection());
     while(onIsection()){goFront();}
   }
   turnILeft();
   halt();
   delay(10000);
}


























