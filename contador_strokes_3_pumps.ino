#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcdA(0x25, 16, 2);
LiquidCrystal_I2C lcdB(0x26, 16, 2);
LiquidCrystal_I2C lcdC(0x27, 16, 2);

const int pin_button0 = 8;
const int pin_button1 = 9;
const int pin_button2 = 10;
bool status_button0 = false;
bool status_button1 = false;
bool status_button2 = false;

int pump1 = 0;
int pump2 = 0;
int pump3 = 0;
int ratePump1 = 0;
int ratePump2 = 0;
int ratePump3 = 0;
int countPump1 = 0;
int countPump2 = 0;
int countPump3 = 0;
long lastTime = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  pinMode(pin_button0, INPUT);
  pinMode(pin_button1, INPUT);
  pinMode(pin_button2, INPUT);

  attachInterrupt(digitalPinToInterrupt(2), counterPump1, RISING);
  attachInterrupt(digitalPinToInterrupt(3), counterPump2, RISING);

  lcdA.init();
  lcdA.backlight();

 
  //
  lcdB.init();
  lcdB.backlight();


  //
  lcdC.init();
  lcdC.backlight();

  lcdA.clear();
  lcdB.clear();
  lcdC.clear();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (millis() - lastTime > 4300 ){
    ratePump1 = countPump1 * 12;
    ratePump2 = countPump2 * 12;
    countPump1 = 0;
    countPump2 = 0;
    lastTime = millis();
  }

    printLcd();

    status_button0 = digitalRead(pin_button0);
    status_button1 = digitalRead(pin_button1);
    status_button2 = digitalRead(pin_button2);

    if (status_button0 == false){
      pump1 = 0;
    }

     if (status_button1 == false){
      pump2 = 0;
    }


 if (status_button2 == false){
      pump3 = 0;
    }

    delay(699);

}

void printLcd(){
  lcdA.clear();
  lcdA.setCursor(0,0);
  lcdA.print("PUMP1: ");
  lcdA.print(ratePump1);
  lcdA.setCursor(0,1);
  lcdA.print("TOTAL: ");
  lcdA.print(pump1);
  
  //
  lcdB.clear();
  lcdB.setCursor(0,0);
  lcdB.print("PUMP2: ");
  lcdB.print(ratePump2);
  lcdB.setCursor(0,1);
  lcdB.print("TOTAL: ");
  lcdB.print(pump2);
  //
  lcdC.clear();
  lcdC.setCursor(0,0);
  lcdC.print("PUMP3: ");
  lcdC.print(ratePump3);
  lcdC.setCursor(0,1);
  lcdC.print("TOTAL: ");
  lcdC.print(pump3);

}

void counterPump1(){
  pump1++;
  countPump1++;
}

void counterPump2(){
  pump2++;
  countPump2++;
}

void counterPump3(){
  pump3++;
  countPump3++;
}