
unsigned long previousMillis=0;
unsigned long interval=200;
int number = 0;
int numToDec=0;
int left = 0;
int right = 0;

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
// put your main code here, to run repeatedly:
  if(Serial.available()){
    number = Serial.read();
    numToDec=number-48;
    
    Serial.println(numToDec, BIN);
    
  }
  /*else {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval){
      previousMillis = currentMillis;
      number = 0;
      Serial.println(number);
    }
  }*/
}

