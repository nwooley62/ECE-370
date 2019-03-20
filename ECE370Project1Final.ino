int pinA = 5;
int pinB = 9;
int IR = 13;
float requested;
int numTicksCounted, numTicksNeeded;
float currentAngle, desiredAngle, angleChange;
float timeStart, timeNow, timeDelay = 100;
boolean slowDown = false;
void setup() {

  Serial.begin(9600);
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(IR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IR), getTick, CHANGE);
  currentAngle = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////
void loop() {

  while(1){
    if(Serial.available()){
      requested = Serial.parseFloat();
      Serial.println(requested);
      numTicksCounted = 0;
      setServo(requested);
      slowDown = false;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////
void stopServo(){
  if(slowDown == true){
    detachInterrupt(digitalPinToInterrupt(IR));
    Serial.println("check 1");
    currentAngle = desiredAngle;                              //save motor position

   /* if(angleChange > 0){                                    //Stop motor momentum
      setVelocity(25);
    }
    else if(angleChange < 0){                                 //need to figure out how to delay the motors so they can stop properly. All solutions give an error when reading from serial device in PuTTy
      setVelocity(250);                                       //have tried a delay(100), a loop of 100 delay(1), and a millis() loop. Using delay() works, however PuTTY throws an error every time
    }
                                                              
    delay(100);*/
    analogWrite(pinA, 0);                                     //Stop motors completely
    analogWrite(pinB, 0);
    attachInterrupt(digitalPinToInterrupt(IR), getTick, CHANGE);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////
void setServo(float degree){

  if(degree > 720){                                           //check if input degrees is greater than +- 720
    degree = 720;
  }else if(degree < -720){
    degree = -720;
  }
  desiredAngle = degree;
  angleChange = desiredAngle - currentAngle;                  //get the distance that the motor needs to travel
  
  numTicksNeeded = abs(angleChange / 360.0) * 75.8 * 4.0;     //set degrees to ticks
  
  if(angleChange > 0){                                        //set velocity based on direciton of travel
    setVelocity(250);
  }
  else if(angleChange < 0){
    setVelocity(5);
  }
  return;
}

///////////////////////////////////////////////////////////////////////////////////////////
void getTick(){

  numTicksCounted++;                                          //increment the number of ticks travelled
  
  
  if(angleChange <= -540){                                       //Since the reverse direction timing is not working, trying the solution of stopping short every time, by different amounts
    if(numTicksCounted > (numTicksNeeded - 260) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= -360){
    if(numTicksCounted > (numTicksNeeded - 200) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= -270){
    if(numTicksCounted > (numTicksNeeded - 150) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= -180){
    if(numTicksCounted > (numTicksNeeded - 110) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= -150){
    if(numTicksCounted > (numTicksNeeded - 100) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= -135){
    if(numTicksCounted > (numTicksNeeded - 90) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= -90){
    if(numTicksCounted > (numTicksNeeded - 60) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= -60){
    if(numTicksCounted > (numTicksNeeded - 20) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= -30){
   if(numTicksCounted > (numTicksNeeded - 0) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    } 
  }else if(angleChange < -15){
    if(numTicksCounted > (numTicksNeeded - 0) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    } 
  }else if(angleChange < 15){                                     
    if(numTicksCounted > (numTicksNeeded - 0) && slowDown == false){//checking for the stopping place    
    slowDown = true;      
    stopServo();
    }
  }else if(angleChange <= 30){
    if(numTicksCounted > (numTicksNeeded - 0) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= 60){
    if(numTicksCounted > (numTicksNeeded - 10) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= 90){
    if(numTicksCounted > (numTicksNeeded - 40) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= 135){
    if(numTicksCounted > (numTicksNeeded - 80) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= 180){
    if(numTicksCounted > (numTicksNeeded - 93) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= 270){
    if(numTicksCounted > (numTicksNeeded - 140) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= 360){
    if(numTicksCounted > (numTicksNeeded - 180) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    }
  }else if(angleChange <= 540){
   if(numTicksCounted > (numTicksNeeded - 150) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    } 
  }else{
    if(numTicksCounted > (numTicksNeeded - 400) && slowDown == false){//checking for the stopping place    
      slowDown = true;      
      stopServo();
    } 
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
