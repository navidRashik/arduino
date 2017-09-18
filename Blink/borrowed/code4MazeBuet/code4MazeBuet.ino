const int analogInPin1=A0, analogInPin2=A1, analogInPin3=A2, analogInPin4=A3, analogInPin5=A4, analogInPin6=A5;
int sensorValue[5]={0,0,0,0,0};
int leftMotor1=3, leftMotor2 =4, rightMotor1 =5, rightMotor2 =6 ,pLight =7 ,hLight =8;
int leftPwm =9,rightPwm =10;
int handler =610;
int face =1;
struct point
{
  
  bool planetPresent;
  int planetMark, crossedTime;
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
struct point presentVertex;
void setup()
{
  pinMode(leftMotor1,OUTPUT); pinMode(leftMotor2,OUTPUT); pinMode(rightMotor1,OUTPUT); pinMode(rightMotor2,OUTPUT);
  pinMode(leftPwm,OUTPUT); pinMode(rightPwm,OUTPUT);
  analogWrite(leftPwm,255); analogWrite(rightPwm,255);
  int i,j;
  Serial.begin(9600);
  for(i=0;i<8;i++)
  {
    for(j=0;j<8;j++)
    {
      vertex[i][j].planetPresent =false;
      vertex[i][j].present=1;
      vertex[i][j].X=i;
      vertex[i][j].Y=j;
      vertex[i][j].planetMark =0;
      vertex[i][j].crossedTime =0;
    }
  }
  randomSeed(analogRead(A0));
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
   for(i=0;i<8;i++)
   {
       for(j=0;j<8;j++)
       {
           vertex[i][j].left=0; vertex[i][j].right=0; vertex[i][j].up=0; vertex[i][j].down=0;
           if(vertex[i+1][j].present==1&&i!=7)vertex[i][j].right=1;
           if(vertex[i-1][j].present==1&&i!=0)vertex[i][j].left=1;
           if(vertex[i][j+1].present==1&&j!=7)vertex[i][j].up=1;
           if(vertex[i][j-1].present==1&&i!=0)vertex[i][j].down=1;
       }
   }
   presentVertex =vertex[7][7];
   
   int l ,m;
   l=7;m=7;
   do
   {
     int randNum =random(4);
     if(randNum ==0)
     {
       if(presentVertex.up==1 && face ==0){do{travel();}while(!onIsection());while(onIsection()){goFront();}m++;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];}
       else if(presentVertex.up ==1 && face ==1){turnIRight();do{travel();}while(!onIsection());while(onIsection()){goFront();}m++;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face=0;}
       else if(presentVertex.up ==1 && face ==2){turnIRight();turnRight();do{travel();}while(!onIsection());while(onIsection()){goFront();}m++;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face=0;}
       else if(presentVertex.up ==1 && face ==3){turnILeft();do{travel();}while(!onIsection());while(onIsection()){goFront();}m++;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face=0;}
       if(vertex[l][m].planetPresent || vertex[l][m].crossedTime >=5)
       {
         vertex[l][m].present =0;
         for(i=0;i<8;i++)
           {
             for(j=0;j<8;j++)
             {
                 vertex[i][j].left=0; vertex[i][j].right=0; vertex[i][j].up=0; vertex[i][j].down=0;
                 if(vertex[i+1][j].present==1&&i!=7)vertex[i][j].right=1;
                 if(vertex[i-1][j].present==1&&i!=0)vertex[i][j].left=1;
                 if(vertex[i][j+1].present==1&&j!=7)vertex[i][j].up=1;
                 if(vertex[i][j-1].present==1&&i!=0)vertex[i][j].down=1;
             }
           }  
       }
      
       
     }
     else if(randNum ==1)
     {
       if(presentVertex.left==1 && face ==0){turnILeft();do{travel();}while(!onIsection());while(onIsection()){goFront();}l--;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face =1;}
       else if(presentVertex.left ==1 && face ==1){do{travel();}while(!onIsection());while(onIsection()){goFront();}l--;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face=1;}
       else if(presentVertex.left ==1 && face ==2){turnIRight();do{travel();}while(!onIsection());while(onIsection()){goFront();}l--;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face=1;}
       else if(presentVertex.left ==1 && face ==3){turnILeft();turnILeft();do{travel();}while(!onIsection());while(onIsection()){goFront();}l--;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face=1;}
       if(vertex[l][m].planetPresent || vertex[i][j].crossedTime >=5)
       {
         vertex[l][m].present =0;
         for(i=0;i<8;i++)
           {
             for(j=0;j<8;j++)
             {
                 vertex[i][j].left=0; vertex[i][j].right=0; vertex[i][j].up=0; vertex[i][j].down=0;
                 if(vertex[i+1][j].present==1&&i!=7)vertex[i][j].right=1;
                 if(vertex[i-1][j].present==1&&i!=0)vertex[i][j].left=1;
                 if(vertex[i][j+1].present==1&&j!=7)vertex[i][j].up=1;
                 if(vertex[i][j-1].present==1&&i!=0)vertex[i][j].down=1;
             }
           }  
       }
     }
     else if(randNum ==2)
     {
       if(presentVertex.down==1 && face ==0){turnILeft();turnILeft();do{travel();}while(!onIsection());while(onIsection()){goFront();}m--;vertex[i][j].crossedTime++;presentVertex=vertex[l][m];face =2;}
       else if(presentVertex.down ==1 && face ==1){turnILeft();do{travel();}while(!onIsection());while(onIsection()){goFront();}m--;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face=2;}
       else if(presentVertex.down ==1 && face ==2){do{travel();}while(!onIsection());while(onIsection()){goFront();}m--;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face=2;}
       else if(presentVertex.down ==1 && face ==3){turnIRight();do{travel();}while(!onIsection());while(onIsection()){goFront();}m--;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face=2;}
       if(vertex[l][m].planetPresent || vertex[i][j].crossedTime >=5)
       {
         vertex[l][m].present =0;
         for(i=0;i<8;i++)
           {
             for(j=0;j<8;j++)
             {
                 vertex[i][j].left=0; vertex[i][j].right=0; vertex[i][j].up=0; vertex[i][j].down=0;
                 if(vertex[i+1][j].present==1&&i!=7)vertex[i][j].right=1;
                 if(vertex[i-1][j].present==1&&i!=0)vertex[i][j].left=1;
                 if(vertex[i][j+1].present==1&&j!=7)vertex[i][j].up=1;
                 if(vertex[i][j-1].present==1&&i!=0)vertex[i][j].down=1;
             }
           }  
       }
     }
     else if(randNum ==3)
     {
       if(presentVertex.right==1 && face ==0){turnIRight();turnILeft();do{travel();}while(!onIsection());while(onIsection()){goFront();}l++;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face =3;}
       else if(presentVertex.right ==1 && face ==1){turnILeft();turnILeft();do{travel();}while(!onIsection());while(onIsection()){goFront();}l++;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face=3;}
       else if(presentVertex.right ==1 && face ==2){turnILeft();do{travel();}while(!onIsection());while(onIsection()){goFront();}l++;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face=3;}
       else if(presentVertex.right ==1 && face ==3){do{travel();}while(!onIsection());while(onIsection()){goFront();}l++;vertex[l][m].crossedTime++;presentVertex=vertex[l][m];face=3;}
       if(vertex[l][m].planetPresent || vertex[i][j].crossedTime >=5)
       {
         vertex[l][m].present =0;
         for(i=0;i<8;i++)
           {
             for(j=0;j<8;j++)
             {
                 vertex[i][j].left=0; vertex[i][j].right=0; vertex[i][j].up=0; vertex[i][j].down=0;
                 if(vertex[i+1][j].present==1&&i!=7)vertex[i][j].right=1;
                 if(vertex[i-1][j].present==1&&i!=0)vertex[i][j].left=1;
                 if(vertex[i][j+1].present==1&&j!=7)vertex[i][j].up=1;
                 if(vertex[i][j-1].present==1&&i!=0)vertex[i][j].down=1;
             }
           }  
       }
     }
   }while(l!=0&& m!=0);
   
   
}


























