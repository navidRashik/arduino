#define leftmotor1 8
#define leftmotor2 7
#define rightmotor1 4
#define rightmotor2 2
#define rightpwm 3
#define leftpwm 6

//sensor
int s1 = A3;
int s2 = A2;
int s3 = A1;
int s4 = A0;


long Kp = 1;
long Ki = 3000;
long Kd = 0;

int error_value=0 ;
//#define white_value 300
int set_point;
int position;
long sensorsAverage;
int sensorsSum;
int left_speed;
int right_speed;
int max_speed = 255;
long proportional;

long derivative;
long last_proportional;
long integral;

long sensors[] = { 0, 0, 0, 0};
long sensorsRead[] = { 0, 0, 0, 0};



void readSensors()
{
  sensors[0]=digitalRead(s1);
  sensors[1]=digitalRead(s2);
  sensors[2]=digitalRead(s3);
  sensors[3]=digitalRead(s4);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(leftmotor1, OUTPUT);
  pinMode(leftmotor2, OUTPUT);
  pinMode(rightmotor1, OUTPUT);
  pinMode(rightmotor2, OUTPUT);
  pinMode(rightpwm, OUTPUT);
  pinMode(leftpwm, OUTPUT);
  setPoint();
  
}

void loop()
{
  sensorsAverage = 0;
  sensorsSum = 0;
  error_value = 0;
  position=0;
 

  readSensors();
  calcPid();
  calc_turn();
  motor_drive(right_speed, left_speed);
  
}
  




void setPoint()
{
  readSensors();
  for (int i = 0; i <4; i++)
  {
    sensorsAverage += sensors[i] * i * 1000; //Calculating the weighted mean
    sensorsSum += int(sensors[i]);
  }
  position = int(sensorsAverage / sensorsSum);
  //set_point=position;
}


void calcPid()
{

  position = int(sensorsAverage / sensorsSum);
  proportional = position - set_point;
  integral = integral + proportional;
  derivative = proportional - last_proportional;
  last_proportional = proportional;
  error_value = int(proportional * Kp + integral * Ki + derivative * Kd);
  //Serial.print(error_value);
  //Serial.print(' ');
}

void calc_turn()
{ //Restricting the error value between +256.
  if (error_value < -max_speed)
  {
    error_value = -max_speed;
  }
  if (error_value > max_speed)
  {
    error_value = max_speed;
  }
  // If error_value is less than zero calculate right turn speed values
  if (error_value < 0)

  {
    left_speed = max_speed + error_value;
    right_speed = max_speed;
  }
  else if (error_value == 0)
  {
    right_speed = max_speed;
    left_speed = max_speed;

  }
  // Iferror_value is greater than zero calculate left turn values
  else
  {
    left_speed = max_speed;
    right_speed = max_speed - error_value;
  }

}

void motor_drive(int right_speed, int left_speed)
{ // Drive motors according to the calculated values for a turn


  digitalWrite(rightmotor1, HIGH);
  digitalWrite(rightmotor2, LOW);
  analogWrite(rightpwm, right_speed);

  digitalWrite(leftmotor1, HIGH);
  digitalWrite(leftmotor2, LOW);
  analogWrite(leftpwm, left_speed);

}




