#define leftmotor1 4
#define leftmotor2 5
#define rightmotor1 7
#define rightmotor2 6
#define rightpwm 8
#define leftpwm 9

long Kp = 1;
long Ki = 3000;
long Kd = 0;

int error_value=0 ;
#define white_value 250
int set_point;
int position;
long sensorsAverage;
int sensorsSum;
int left_speed;
int right_speed;
int max_speed = 150;
long proportional;

long derivative;
long last_proportional;
long integral;

long sensors[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
long sensorsRead[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

double lff = 0;
double lf = 0;
double ln = 0;
double lc = 0;
double rc = 0;
double rn = 0;
double rf = 0;
double rff = 0;
double center = 0;//  this is the center point 


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
   Serial.print("\n");
    
  
  

}
  



void readSensors()
{
  int port = 7; //input of sensors port for mega..
  for (int i = 0; i <9; i++)
  {

    sensors[i] = analogRead(port);
    sensorsAverage += sensors[i] * i * 1000; //Calculating the weighted mean
    sensorsSum += int(sensors[i]);
    port++;
  }
  position = int(sensorsAverage / sensorsSum);

  //Serial.print(sensorsAverage);
 // Serial.print(' ');
  //Serial.print(sensorsSum);
  //Serial.print(' ');
  Serial.print(position);
  Serial.print(' ');
   //delay(0);


}
void setPoint()
{
  int port = 7;
  for (int i = 0; i <9; i++)
  {
    
    sensors[i] = analogRead(port);
    sensorsAverage += sensors[i] * i * 1000; //Calculating the weighted mean
    sensorsSum += int(sensors[i]);
    port++;
  }
  position = int(sensorsAverage / sensorsSum);
  set_point=position;
  Serial.print(set_point);
  Serial.print(" ");
   //delay(0);


}
void calcPid()
{

  position = int(sensorsAverage / sensorsSum);
  proportional = position - set_point;
  integral = integral + proportional;
  derivative = proportional - last_proportional;
  last_proportional = proportional;
  error_value = int(proportional * Kp + integral * Ki + derivative * Kd);
  Serial.print(error_value);
  Serial.print(' ');
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

  Serial.print(left_speed);
  Serial.print(' ');
  Serial.print(right_speed);
  Serial.print(' ');
  Serial.println();
  digitalWrite(rightmotor1, HIGH);
  digitalWrite(rightmotor2, LOW);
  analogWrite(rightpwm, right_speed);

  digitalWrite(leftmotor1, HIGH);
  digitalWrite(leftmotor2, LOW);
  analogWrite(leftpwm, left_speed);

//  delay(50); // Optional
}

void readSensorsTurn()
{
  int port = 7;
  for (int i = 0; i <9 ; i++)
  {
 
    
    sensorsRead[i] = analogRead(port);
    port++;
  }
  center = sensorsRead[0];
  lff = sensorsRead[1];
  lf = sensorsRead[2];
  ln = sensorsRead[3];
  lc = sensorsRead[4];
  rc = sensorsRead[5];
  rn = sensorsRead[6];
  rf = sensorsRead[7];
  rff = sensorsRead[8];
  
 
  Serial.print(center);
  Serial.print(' ');

  Serial.print(lff);
  Serial.print(' ');

  Serial.print(lf);
  Serial.print(' ');

  Serial.print(ln);
  Serial.print(' ');

  Serial.print(lc);
  Serial.print(' ');

  Serial.print(rc);
  Serial.print(' ');

  Serial.print(rn);
  Serial.print(' ');

  Serial.print(rf);
  Serial.print(' ');

  Serial.print(rff);
  Serial.print(' ');

  Serial.println();

}


