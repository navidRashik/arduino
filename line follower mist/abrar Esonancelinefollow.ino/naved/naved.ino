#include <QTRSensors.h>

#define Kp 4 // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd 300// experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 
//#define Ki 0.001
#define rightMaxSpeed 250 // max speed of the robot
#define leftMaxSpeed 250 // max speed of the robot
#define rightBaseSpeed 190 // this is the speed at which the motors should spin when the robot is perfectly on the line
#define leftBaseSpeed 190  // this is the speed at which the motors should spin when the robot is perfectly on the line
#define NUM_SENSORS  8     // number of sensors used
#define TIMEOUT  2500  // waits for 2500 us for sensor outputs to go low
#define EMITTER_PIN   31     // emitter is controlled by digital pin 2
#define DEBUG 0
#define rightMotor1 7
#define rightMotor2 8
#define rightMotorPWM 6
#define leftMotor1 2
#define leftMotor2 4
#define leftMotorPWM 3 
#define ledRed 13
#define ledYellow 12
#define ledGreen 11
int  setPoint=0; 
#define  right_sensor 15
#define  left_sensor 8
#define  center_sensor 7

QTRSensorsRC qtrrc((unsigned char[]) {  0, 1, 2, 3, 4, 5, 9, 10} ,NUM_SENSORS, TIMEOUT, EMITTER_PIN); // sensor connected through analog pins A0 - A5 i.e. digital pins 14-19

boolean center=0;
boolean right=0;
boolean left=0;
unsigned int sensors[8];
void setup()
{

  Serial.begin(9600);  
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(ledRed,OUTPUT);
  pinMode(ledYellow,OUTPUT);
  pinMode(ledGreen,OUTPUT);
  digitalWrite(ledRed,LOW);
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledYellow,LOW);
  delay(500);
  digitalWrite(ledRed,HIGH);
  manual_calibration();
  digitalWrite(ledRed,LOW);
  digitalWrite(ledYellow,HIGH);
  set_point();
  digitalWrite(ledYellow,LOW);
  digitalWrite(ledGreen,HIGH); 
 
 }

int lastError = 0;
int integral=0;

void loop()
{  
      PID_control();
      
}



 
void hudai()
{   read_sensor();
    if(left==1&&center==0)
      turn_left();
      else if(right==1&&center==0)
      turn_right();
   


  
}
 void PID_control(){
   
   int position = qtrrc.readLine(sensors); // get calibrated readings along with the line position, refer to the QTR Sensors Arduino Library for more details on line position.
  int error = position - setPoint;
  integral = integral + error;
  int motorSpeed = Kp * error + Kd * (error - lastError);//+Ki*integral;
  lastError = error;

  int rightMotorSpeed = rightBaseSpeed + motorSpeed;
  int leftMotorSpeed = leftBaseSpeed - motorSpeed;
  
    if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed; // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = 0; // keep the motor speed positive
  if (leftMotorSpeed < 0) leftMotorSpeed = 0; // keep the motor speed positive
  
   {
// move forward with appropriate speeds
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  analogWrite(rightMotorPWM, rightMotorSpeed);
 
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM, leftMotorSpeed);
}

   
}
void set_point(){
  for(int i=0;i<100;i++)
  {
    setPoint= qtrrc.readLine(sensors);
    delay(20);
  }
  
}

void read_sensor(){
      
    boolean center=analogRead(center_sensor)>400;
    boolean right=analogRead(right_sensor)>400;
    boolean left=analogRead(left_sensor)>400;

  Serial.print(left);
  Serial.print("  ");
  Serial.print(center);
  Serial.print("  ");
  Serial.print(right);
  Serial.print("  ");
  Serial.println();


}

void turn_left(){
    digitalWrite(ledRed,HIGH);
    while(!center){
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
     analogWrite(leftMotorPWM, leftBaseSpeed);
     analogWrite(rightMotorPWM, rightBaseSpeed);
    }
}


void turn_right(){
  
      digitalWrite(ledRed,HIGH);
    while(!center){
    digitalWrite(rightMotor1,LOW);
    digitalWrite(rightMotor2, HIGH);
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
     analogWrite(leftMotorPWM, leftBaseSpeed);
     analogWrite(rightMotorPWM,rightBaseSpeed);
    }
  
  
   }



void manual_calibration() {
 
int i;
for (i = 0; i < 100; i++)
{
qtrrc.calibrate(QTR_EMITTERS_ON);
delay(20);
}
 
if (DEBUG) {
Serial.begin(9600);
for (int i = 0; i < NUM_SENSORS; i++)
{
Serial.print(qtrrc.calibratedMinimumOn[i]);
Serial.print(' ');
}
Serial.println();
 
for (int i = 0; i < NUM_SENSORS; i++)
{
Serial.print(qtrrc.calibratedMaximumOn[i]);
Serial.print(' ');
}
Serial.println();
Serial.println();
}
}

 

