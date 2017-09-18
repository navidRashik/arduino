     
//Motor left
int enableA = 6;
int MotorA1 = 7;
int MotorA2 = 8;
 
//Motor right
int enableB = 3;
int MotorB1 = 2;
int MotorB2 = 4;


//sensor
int s1 = A0;
int s2 = A1;
int s3 = A2;
int s4 = A3;
int s5 = A4;
int s6 = A5;
int s7 = 9;
int s8 = 10;

//pid
float sumEqn=0;
float sum=0;
float position=0;
float set_point=0;
float proportional=0;
float integral=0;
float derivative=0;
float last_proportional=0;
float error_value=0;

//const pid 
float Kp=30;
float Ki=0.000;//.001;
float Kd=0000;

//pid motor controll
int left_speed;
int right_speed;
float base_speed=120; //also running speed
float max_speed=255-base_speed; //max255


bool frontGap=false;
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
  //delay(1000);
  setPoint();
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
       
//    Serial.print(sensorValue[7]);
//    Serial.println(" ");
}


void calculateSensors()
{
    readSensors();
  
    for(int i=0 ;i<8;i++)
    {
      sumEqn+=(sensorValue[i]*10*(i+1));
      sum+=sensorValue[i];
    }
    position=(sumEqn/sum);
    
//    Serial.print(position);
//    Serial.println(" ");
}

void setPoint()
{
    readSensors();
    for(int i=0 ;i<8;i++)
    {
      sumEqn+=(sensorValue[i]*10*(i+1));
      sum+=sensorValue[i];
    }
    position=(sumEqn/sum);
    set_point=position;
    
//    Serial.print(set_point);
//    Serial.println(" ");
}


void calcPid()
{
  
  position = int(sumEqn / sum);
  proportional = position - set_point;
  integral = integral + proportional;
  derivative = proportional - last_proportional;
  last_proportional = proportional;
  error_value = (proportional*Kp)+(integral*Ki)+(derivative*Kd);
  Serial.print(integral);
  Serial.print(' ');
}

void motor_drive(int right_speed, int left_speed)
{ 
  // Drive motors according to the calculated values for a turn

  
  Serial.print(right_speed); //left
  Serial.print(' ');
  Serial.print(left_speed); //r8
  Serial.print(' ');
  Serial.println();

    digitalWrite (MotorA1, LOW);  //left motor
    digitalWrite (MotorA2, HIGH);
    analogWrite(enableA, left_speed);
    
    digitalWrite (MotorB1, LOW);  //r8 motor
    digitalWrite (MotorB2, HIGH);
    analogWrite(enableB, right_speed);  


}


void calc_turn()
{ //Restricting the error value between +256.
  int sub_err=error_value;
  if (error_value < -base_speed )
  {
    error_value = -base_speed;
    
  }
  
  if (sub_err<-max_speed )
  {
    sub_err=-max_speed;
  }

  
  if (error_value > base_speed)
  {
    error_value = base_speed;
  }

  if (sub_err>max_speed )
  {
    sub_err=max_speed;
  }

  // If error_value is less than zero calculate right turn speed values
  if (error_value < 0)
  {
    left_speed = base_speed + error_value;
    right_speed = base_speed-sub_err;
  }
  else if (error_value == 0)
  {
    right_speed = base_speed;
    left_speed = base_speed;

  }
  // Iferror_value is greater than zero calculate left turn values
  else
  {
    left_speed = base_speed+sub_err;
    right_speed = base_speed - error_value;
  }

}



void loop() {
  
//  analogWrite (enableA, 228);
//  analogWrite (enableB, 228);

  sumEqn=0;
  sum=0;
  error_value=0;
  position=0;
  
  calculateSensors();
  calcPid();
  calc_turn();
  motor_drive(right_speed, left_speed);
  //only_p();
  //travel();
  //turnRight();
  //digitalRead(s1);
}


/*
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

    avg=(sum/track);

    if(avg<40 && avg>30)
    {
      goLeft();
    }
    else if(avg>50 &&  avg<60)
    {
      goRight();
    }
    if(avg<30)
    {
      turnLeft();
    }
    else if(avg>60)
    {
      turnRight();
    }
    
    else if(avg>=40 && avg<=50)
    {
      goFront();
    }
    Serial.println(avg );
    
}

bool onLine()
{
  readSensors();
  if(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==0 && sensorValue[4]==0){
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
    Serial.println("00100" );
  }else if(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==1 && sensorValue[4]==0)
  {
    goRight();
    
    Serial.println("00110");
  }
  else if(sensorValue[0]==0 && sensorValue[1]==1 && sensorValue[2]==1 && sensorValue[3]==0 && sensorValue[4]==0)
  {
    goLeft();
    
    Serial.println("01100" );
  }
  else if(sensorValue[0]==1 && sensorValue[1]==1 && sensorValue[2]==1 && sensorValue[3]==1 && sensorValue[4]==1)
  {
    goFront();
    Serial.println("11111" );
  }
    else if(sensorValue[0]==1 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==0 && sensorValue[4]==0)
  {
    goFront();
    delay(400);
    Serial.println("10100" );
//    if(sensorValue[0]==1 && sensorValue[1]==1 && sensorValue[2]==1 && sensorValue[3]==0 && sensorValue[4]==0){
//      while(!(sensorValue[0]==0 && sensorValue[1]==1 && sensorValue[2]==1 && sensorValue[3]==0 && sensorValue[4]==0) || !(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==0 && sensorValue[4]==0)){
//        readSensors();
//        goFront();
//        Serial.println("11100 sp case" ); //sp case
//      }
//    }
  }
    else if(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==0 && sensorValue[4]==1)
  {
    goFront();
    delay(400);
    Serial.println("00101" ); //sp case
//    if(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==1 && sensorValue[4]==1){
//      while(!(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==1 && sensorValue[4]==0) || !(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==0 && sensorValue[4]==0)){
//        readSensors();
//        goFront();
//        Serial.println("00111 sp case" ); //sp case
//      }
      
//    }
  }
  
    else if(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==0 && sensorValue[3]==0 && sensorValue[4]==0)
  {
    //if(digitalRead(back)==1) goFront(); 
    goFront();
    Serial.println("00000" );
  }
  else if(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==1 && sensorValue[4]==1)
  {
    Serial.println("00111" );
    while(!(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==1 && sensorValue[4]==0))
    {
      //analogWrite (enableB, 217);
      readSensors();
      turnRight();
    }
  }
  else if(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==0 && sensorValue[3]==1 && sensorValue[4]==1)
  {
    Serial.println("00011" );
    while(!(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==0 && sensorValue[4]==0))
    {
      readSensors();
      goRight();
    }
  }
  else if(sensorValue[0]==1 && sensorValue[1]==1 && sensorValue[2]==1 && sensorValue[3]==0 && sensorValue[4]==0)
  {
    Serial.println("11100" );
    while(!(sensorValue[0]==0 && sensorValue[1]==1 && sensorValue[2]==1 && sensorValue[3]==0 && sensorValue[4]==0))
    {
      readSensors();
      turnLeft();
    }
  }
  else if(sensorValue[0]==1 && sensorValue[1]==1 && sensorValue[2]==0 && sensorValue[3]==0 && sensorValue[4]==0)
  {
    Serial.println("11000" );
    while(!(sensorValue[0]==0 && sensorValue[1]==0 && sensorValue[2]==1 && sensorValue[3]==0 && sensorValue[4]==0))
    {
      readSensors();
      goLeft();
    }
  }

}
*/
/*
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
*/



