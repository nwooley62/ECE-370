int pinA = 5;
int pinB = 9;
int IR = 10;
int const num = 10;
int readIndex = 0;
float t1 = 0, t2 = 0, delta = 0;
float times[num], total, average, input = 0, output;
int sign;
float requested;
float currentOffset = 1, curentVelocity = 127;

void setup() {

  Serial.begin(9600);
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(IR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IR), findSpeed, CHANGE);

  for(int i = 0; i < num; i++){
    times[i] = 0;
  }
}

void loop() {

  while(1){
    if(Serial.available()){
      currentOffset = 1;
      requested = Serial.parseFloat();
      Serial.println(requested);
      set();
      //setVelocity(Serial.parseFloat());
    }
    check();
  }

}

void set(){
  if(requested < 0) sign = -1;
    else sign = 1;

  if (requested > output)
  {
    //setVelocity(currentVelocity + (currentOffset));
    setVelocity(254);
  }
  else if (requested < output)
  {
    //setVelocity(currentVelocity - (currentOffset));
    setVelocity(0);
  }
}

void check()
{
  if (abs(requested - output) > 0.005)
  {
    //currentOffset *= 1.01;
    //if(currentOffset > 1.5) currentOffset = 1.5;
    set();
  }
  else
  {
    currentOffset = 1;
  }
}


void setVelocity(float velocity){
  
   if(velocity >= 127) {
    digitalWrite(pinA, LOW);
    analogWrite(pinB, (velocity-127)*2);
  }
  if(velocity < 127) {
    digitalWrite(pinB, LOW);
    analogWrite(pinA, (127-velocity)*2);
  }
  //Serial.print(velocity);
  return;
}

void findSpeed(){
  t1 = t2;
  t2 = millis();

  delta = t2 - t1;

  total = total - times[readIndex];
  times[readIndex] = delta;
  total = total + times[readIndex];
  readIndex++;

  if(readIndex >= num)
    readIndex = 0;
    
  average = total/num;


  input = 1000/ (4 * average);
  output = input/75.81;

  Serial.println(output);
}
