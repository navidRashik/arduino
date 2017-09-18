int s1 = A0;
int s2 = A1;
int s3 = A2;
int s4 = A3;
int s5 = A4;
int s6 = A5;
int s7 = 9;
int s8 = 10;
void setup() {
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
void loop() {
  Serial.print("no 1  " );
  Serial.println(digitalRead(s1));
  Serial.print("no 2  " );
  Serial.println(digitalRead(s2));
  Serial.print("no 3  " );
  Serial.println(digitalRead(s3));
  Serial.print("no 4  " );
  Serial.println(digitalRead(s4));
   Serial.print("no 5  " );
  Serial.println(digitalRead(s5));
  Serial.print("no 6  " );
  Serial.println(digitalRead(s6));
  Serial.print("no 7  " );
  Serial.println(digitalRead(s7));
  Serial.print("no 8  " );
  Serial.println(digitalRead(s8));
  
  delay(2000);        // delay in between reads for stability
}



