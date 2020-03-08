#include <Servo.h>

// echo
int echo = 12;
int trig = 13;
float t = 0;
float distance = 0;

// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;
bool itemFound = false;
int turn = 0;
double prvTurnTime = 0;
//double seconds = millis()*0.001;

//amount of time to move forward when item in range
int doorStatus=0; //close = 0
                  //open = 1
int turnStatus=0;

//ML vars
unsigned long previousMillis=0;
unsigned long interval=200;
int number = 0;
int numToDec=0;
int left = 0;
int right = 0;

////Servo Motor
//int servoPin = 3;
// 
//Servo servo;  
// 
//int servoAngle = 0;   // servo position in degrees
//int servoMax = 120;
//int servoMin = 0;
// 


void setup() {
  // put your setup code here, to run once:
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  Serial.begin(9600);

  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

//    Serial.begin(9600);  
//  servo.attach(servoPin);
  
}

void stop(){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW); 
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW); 
}

void backwards(){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH); 
      analogWrite(enA, 225); 
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); 
      analogWrite(enB, 200);
}

void forwards(){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 225);  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, 200);
   
}

void turnLeftCheck(){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 250);  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, 50);
    delay(100);//small 
}

void turnRight(){
     digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 50);  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, 250);
    Serial.println("turn left");
    delay(525);
}

void turnRightCheck(){
     digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 250);  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, 50);
    Serial.println("turn left");
    delay(100);
}

void printDistance(){
    //echo
  digitalWrite(trig,LOW);
  delay(50);
  digitalWrite(trig,HIGH);
  delay(50);
  digitalWrite(trig,LOW);
  t = pulseIn(echo,HIGH);
  distance = ((340*t)/2 )*0.0001; //Not sure how many cm
  Serial.print(distance);
  Serial.println(" cm");
}
void loop() {
  
  if(Serial.available()){
    number = Serial.read();
    turnStatus=number-48;
    itemFound=true;
    Serial.println(turnStatus, BIN);
    
  }else{
    itemFound=false;
  }

  printDistance();
  
 if(itemFound == false ){
    forwards();
    Serial.println(prvTurnTime);
    if(((millis()*0.001- prvTurnTime) < 12) && ((millis()*0.001- prvTurnTime) > 6) && itemFound == false){
      //reset prvTurnTime when item is finished being found Found
      prvTurnTime = millis()*0.001;
      turnRight();
      turn = turn +1; //first turn
      //delay(225); //angle

    }
 }
/*
  for(servoAngle = servoMin; servoAngle < servoMax; servoAngle = servoAngle + 5)  //move the micro servo from 0 degrees to 90 degrees
  {                                  
    servo.write(servoAngle);              
    delay(10);                  
  }
 
  for(servoAngle = servoMax; servoAngle > servoMin; servoAngle = servoAngle - 1)  //now move back the micro servo from 0 degrees to 90 degrees
  {                                
    servo.write(servoAngle);          
    delay(10);      
  }
  //end control the servo's speed  
         
  delay(1000);  
*/

  //turn left or right to find next item
  if(itemFound == true){
    if(turnStatus==5){
      turnRightCheck();  
    }else if(turnStatus==6){
      turnLeftCheck();
    }else if(turnStatus==4){
          Serial.println("Item found");
          printDistance();
          if(distance>17){
            Serial.println("greater than 15");
            forwards();
            printDistance();
          }
          if(distance < 20 && distance > 10){
            Serial.println("greater than 15, less than 10");
            doorStatus=1;
            //openDoor();
            stop();
            delay(2000);
            forwards(); //for x amount of time
            printDistance();  
        }
          if(distance < 10 && distance > 8){
            Serial.println("greater than 10, less than 8");
            doorStatus=0;
            stop();
            delay(2000);
            prvTurnTime = millis()*0.001;
            itemFound = false;
            printDistance();
            //closeDoor();
          }
          if(distance<8){
            backwards();
          }
    }
  }

}
