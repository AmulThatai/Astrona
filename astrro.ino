#define CS 10 //chip select pin
#define IN A0 //analog input pin
#include <SPI.h> // Call library

//custom macros//
#define DIR_FORWARD 1
#define DIR_REVERSE 2
#define STOP 0

//relay pinouts//
#define Stop 3 //LI1
#define Forward 4 //LI2
#define Reverse 5 //LI3


String inString = "";
int Serial_Int = 0;


void RUN_COND();
void STOP_COND();
void setup() {
  pinMode(Stop,OUTPUT);
  pinMode(Forward,OUTPUT);
  pinMode(Reverse,OUTPUT);
  Serial.begin(9600); // initialization of the serial port
  SPI.begin(); // initialization of SPI interface
  SPI.setDataMode(SPI_MODE0); // configuration of SPI communication in mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV16); // configuration of clock at 1MHz
  pinMode(CS, OUTPUT); //setting chip select as output
  while (!Serial) {
    ;
  }
  Serial.println("\n\nString toInt():");
  Serial.println();
  setDirection(DIR_FORWARD);
}

void loop() {
//  Serial.println("full speed, forward");
//  setDirection(DIR_FORWARD);
//  writeSpeed(100);
//  delay(7000);
//  Serial.println("full speed, reverse");
//  setDirection(DIR_REVERSE);
//  delay(14000);
//  Serial.println("30% speed, reverse");
//  writeSpeed(30);
//  delay(7000);
//  Serial.print("STOP");
//  setDirection(STOP);
//  delay(7000);
//  Serial.println("REVERSE, 30% speed");
//  setDirection(DIR_REVERSE);
//  delay(14000);
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      inString += (char)inChar;
    }
    if (inChar == '#') {
      Serial_Int = inString.toInt();
      Serial.print("Value:");
      Serial.println(Serial_Int);
      Serial.print("String: ");
      Serial.println(inString);
      inString = "";
    }
  }

  
  writeSpeed(Serial_Int);
}
void STOP_COND(){
  digitalWrite(Stop,HIGH); 
}
void setDirection(int DIR){
  if(DIR == DIR_FORWARD){
//    digitalWrite(Reverse,HIGH);
//    digitalWrite(Stop,LOW);
//    delay(500);
//    digitalWrite(Forward,LOW);
//    delay(200);
//    digitalWrite(Forward,HIGH);

//  Default_Condition();
  RUN_COND();
  delay(500);
  digitalWrite(Forward,LOW);
  }
  else if(DIR == DIR_REVERSE){
//    digitalWrite(Forward,HIGH);
//    digitalWrite(Stop,LOW);
//    delay(500);
//    digitalWrite(Reverse,LOW);
//    delay(200);
//    digitalWrite(Reverse,HIGH);
RUN_COND();
delay(500);
digitalWrite(Reverse,LOW);

  }
  else if(DIR == STOP){
    STOP_COND();
  }
}

void RUN_COND(){
  digitalWrite(Stop,LOW); 
  digitalWrite(Forward,HIGH);
  digitalWrite(Reverse,HIGH);
}

void writeSpeed(int vout){
  digitalWrite(CS, LOW); // activation of CS line
  delayMicroseconds(15);
  int finalVout = (int)map(vout,0,100,0,255);
  SPI.transfer(finalVout); // Send the variable i (i=0->Vout=0V i=255->Vout=Vcc)
  Serial.println("beepboop " + (String)finalVout);
  digitalWrite(CS, HIGH); // deactivation of CS line
}
