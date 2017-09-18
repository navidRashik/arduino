const int led=9;
const int button=2;
bool crrState=LOW;
bool lastState= LOW;
bool ledOn=false;
void setup() {
  // put your setup code here, to run once:
  pinMode (led, OUTPUT);
  pinMode (button, INPUT);

}

bool debounce(bool last)
{
  bool current=digitalRead(button);
  if(last!=current)
  {
    delay(7);
    if(current==digitalRead(button))
    {
      return current;
    }
    
  }
  return last;
}

void loop() {
  crrState=debounce(lastState);
  if(lastState==LOW && crrState==HIGH)
  {
    ledOn=!ledOn;
    
  }
  lastState=crrState;
  digitalWrite(led, ledOn);
}
