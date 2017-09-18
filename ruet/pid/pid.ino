     
//Motor left
int enableA = 11;
int MotorA1 = 5;
int MotorA2 = 4;
 
//Motor right
int enableB = 10;
int MotorB1 = 7;
int MotorB2 = 6;


//sensor
int s1 = A0;
int s2 = A1;
int s3 = A2;
int s4 = A3;
int s5 = A4;
int s6 = A5;
int s7 = A6;
int s8 = A7;

//pid
float sumEqn=0;
float sumSensor=0;
float sum=0;
float position=0;
float proportional=0;
float integral=0;
float derivative=0;
float last_proportional=0;
float error_value=0;

//const pid 
float Kp=7;
float Ki=0;//.001;
float Kd=0;//20000
float set_point=1500;//fixed
int err_range=740*kp;

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
  Serial.begin(9600);

}

void loop() {
  
//  analogWrite (enableA, 228);
//  analogWrite (enableB, 228);

  sumEqn=0;
  sum=0;
  error_value=0;
  position=0;
  
  //read sensors ::
//  sensorValue[0]=analogRead(s1);
//  sensorValue[1]=analogRead(s2);
//  sensorValue[2]=analogRead(s3);
//  sensorValue[3]=analogRead(s4);
//  sensorValue[4]=analogRead(s5);
//  sensorValue[5]=analogRead(s6);
//  sensorValue[6]=analogRead(s7);
//  sensorValue[7]=analogRead(s8);
  

//using only 4
  sensorValue[0]=analogRead(s3);
  sensorValue[1]=analogRead(s4);
  sensorValue[2]=analogRead(s5);
  sensorValue[3]=analogRead(s6);
  for(int i=0;i<4;i++){
    Serial.print("sv::");
    Serial.print(i);
    Serial.print("   ");
    Serial.print(sensorValue[i]);
    
    
  }
  Serial.println();
  //delay(1000);

  //calculate sensors ::
  for(int i=0 ;i<4;i++)
    {
      sumEqn+=(sensorValue[i]*i*1);
      Serial.print("junction a : ");
      Serial.println(sumEqn);
      sum+=sensorValue[i];
      
    }

  //calculate Pid ::
  position = 1000*(sumEqn / sum);
  proportional = position - set_point;
  integral = integral + proportional;
  derivative = proportional - last_proportional;
  last_proportional = proportional;
  error_value = (proportional*Kp)+(integral*Ki)+(derivative*Kd);
  Serial.println(error_value);
  Serial.print(' ');
  //delay(1000);
  
  //calc_turn
  //Restricting the error value between +256
  int err_pwm_neg_r = map(error_value,-err_range,err_range,0,160);
  int err_pwm_neg_l = map(error_value,-err_range,err_range,160,0);
  int err_pwm = map(error_value,-err_range,err_range,0,max_speed);
  if (error_value < 0)
  {
    //turn left
    left_speed = base_speed - err_pwm_neg_l;
    right_speed = base_speed + err_pwm;
    Serial.println(left_speed);
  Serial.print(' ');
  //delay(1000);
  }
  else if (error_value > 0)
  {
    //turn r8
    left_speed = base_speed + err_pwm;
    right_speed = base_speed - err_pwm_neg_r;
  }
  
  //motor_drive(right_speed, left_speed) ::
  digitalWrite (MotorA1, LOW);  //left motor
  digitalWrite (MotorA2, HIGH);
  analogWrite(enableA, left_speed);
  
  digitalWrite (MotorB1, LOW);  //r8 motor
  digitalWrite (MotorB2, HIGH);
  analogWrite(enableB, right_speed);  

  
  
   
//  calculateSensors();
//  calcPid();
//  calc_turn();
//  motor_drive(right_speed, left_speed);


  //only_p();
  //travel();
  //turnRight();
  //digitalRead(s1);
}



















//
//void readSensors()
//{
//  sensorValue[0]=analogRead(s1);
//  sensorValue[1]=analogRead(s2);
//  sensorValue[2]=analogRead(s3);
//  sensorValue[3]=analogRead(s4);
//  sensorValue[4]=analogRead(s5);
//  sensorValue[5]=analogRead(s6);
//  sensorValue[6]=analogRead(s7);
//  sensorValue[7]=analogRead(s8);
//       
////    Serial.print(sensorValue[7]);
////    Serial.println(" ");
//}
//
//
//void calculateSensors()
//{
//    readSensors();
//  
//    for(int i=0 ;i<7;i++)
//    {
//      sumEqn+=(sensorValue[i]*1000);
//      sum+=sensorValue[i];
//      
//    }
//    position=(sumEqn/sum);
//    
//    
////    Serial.print(position);
////    Serial.println(" ");
//}
//
//void setPoint()
//{
//    readSensors();
//    for(int i=0 ;i<7;i++)
//    {
//      sumEqn+=(sensorValue[i]*1000;
//      sum+=sensorValue[i];
//    }
//    position=(sumEqn/sum);
//    set_point=position;
//    
////    Serial.print(set_point);
////    Serial.println(" ");
//}
//
//
//void calcPid()
//{
//  
//  position = int(sumEqn / sum);
//  proportional = position - set_point;
//  integral = integral + proportional;
//  derivative = proportional - last_proportional;
//  last_proportional = proportional;
//  error_value = (proportional*Kp)+(integral*Ki)+(derivative*Kd);
//  Serial.print(integral);
//  Serial.print(' ');
//}
//
//void motor_drive(int right_speed, int left_speed)
//{ 
//  // Drive motors according to the calculated values for a turn
//
//  
//  Serial.print(right_speed); //left
//  Serial.print(' ');
//  Serial.print(left_speed); //r8
//  Serial.print(' ');
//  Serial.println();
//
//  digitalWrite (MotorA1, LOW);  //left motor
//  digitalWrite (MotorA2, HIGH);
//  analogWrite(enableA, left_speed);
//  
//  digitalWrite (MotorB1, LOW);  //r8 motor
//  digitalWrite (MotorB2, HIGH);
//  analogWrite(enableB, right_speed);  
//
//
//}
//
//
//void calc_turn()
//{ //Restricting the error value between +256.
//  int sub_err=error_value;
//  if (error_value < -base_speed )
//  {
//    error_value = -base_speed;
//    
//  }
//  
//  if (sub_err<-max_speed )
//  {
//    sub_err=-max_speed;
//  }
//
//  
//  if (error_value > base_speed)
//  {
//    error_value = base_speed;
//  }
//
//  if (sub_err>max_speed )
//  {
//    sub_err=max_speed;
//  }
//
//  // If error_value is less than zero calculate right turn speed values
//  if (error_value < 0)
//  {
//    left_speed = base_speed + error_value;
//    right_speed = base_speed-sub_err;
//  }
//  else if (error_value == 0)
//  {
//    right_speed = base_speed;
//    left_speed = base_speed;
//
//  }
//  // Iferror_value is greater than zero calculate left turn values
//  else
//  {
//    left_speed = base_speed+sub_err;
//    right_speed = base_speed - error_value;
//  }
//
//}
//

