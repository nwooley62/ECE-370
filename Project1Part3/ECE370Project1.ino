int pinA = 5;
int pinB = 9;
int IR = 10;
int const num = 10;
int readIndex = 0;
float t1 = 0, t2 = 0, delta = 0;
float times[num], total,average;

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
      setVelocity(Serial.parseFloat());
    }
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
  Serial.print(velocity);
  return;
}

void findSpeed(){
  t1 = t2;
  t2 = millis();

  delta = t2 - t1;

  total = total - times[readIndex];
  times[readIndex] = delta;
  readIndex++;

  if(readIndex >= num)
    readIndex = 0;
  average = total/num;
  Serial.println(average);
  
}
