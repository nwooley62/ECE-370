#define pinA 5
#define pinB 9
#define IRA 13
#define IRB 12

float requested = 0;
int numTicksCounted = 0;
float currentAngle = 0;
int IRoutA, IRoutB;
int time1, time2;
float Kp = 7;
float error, output, angle, motor;
float t1, t2;
int incoming[6];
int sign, modSum, divSum, checkSum;
int dir;
void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(IRB, INPUT);
  pinMode(IRA, INPUT);
  attachInterrupt(digitalPinToInterrupt(IRA), getTick, CHANGE);
  currentAngle = 0;
  t1 = millis();

}
////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
while(true){
  if(Serial1.available() >= 6){
    for(int i = 0; i < 7; i++){
      incoming[i] = (Serial1.read());
      Serial.println(incoming[i]);
    }
  }
  if(incoming[0] == 255 && incoming[1] == 255){
    sign = incoming[2];
    divSum = incoming[3] * 256;
    modSum = incoming[4];
    checkSum = 255 % (sign + divSum + modSum);
    requested = divSum + modSum;
    if(checkSum == incoming[5]){
      if(sign > 0){
        requested = abs(requested);
        Serial.println(requested);
      }else{
          requested = -1 * abs(requested);
        Serial.println(requested);
      }
    }
  }
  if(requested > 720){ requested = 720;}
  else if(requested < -720) {requested = -720;}
  currentAngle = getAngle(numTicksCounted);
  
  t1 = millis();
  if(t1 - t2 >= 20){
    motor = pControl(requested, currentAngle) + 127;
    setVelocity(motor);
    t2 = t1;
  }
}
}
///////////////////////////////////////////////////////////////////////////////////////////
void getTick(){

  IRoutA = digitalRead(IRA);
  IRoutB = digitalRead(IRB);

  if(IRoutA != IRoutB){
    numTicksCounted++;
  }else{
    numTicksCounted--;
  }  
}

///////////////////////////////////////////////////////////////////////////////////////////

void setVelocity(float velocity){                             //sets the velocity of the motor
  
   if(velocity >= 127) {
    digitalWrite(pinA, LOW);
    analogWrite(pinB, (velocity-127)*2);
  }
  if(velocity < 127) {
    digitalWrite(pinB, LOW);
    analogWrite(pinA, (127-velocity)*2);
  }
  return;
}

///////////////////////////////////////////////////////////////////////////////////////////


float getAngle(int count){
  angle = count * 1.2; //1.2 degrees per tick
  return angle;
  
}

///////////////////////////////////////////////////////////////////////////////////////////

float pControl(float desiredAngle, float angle){
  error = desiredAngle - angle;
  output = (error*Kp);
  return output;
}
