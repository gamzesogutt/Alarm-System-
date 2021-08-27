#include <SoftwareSerial.h>
#include <LiquidCrystal.h> 
#include <EEPROM.h>
LiquidCrystal lcd(12,11,8,9,6,7);

void Durdur();
int Alarm ;
char veri;
int uyariBuzzerPin = 10;
int uyariKirmiziLedPin = 13;
int uyariYesilLedPin = 5;
int kesmeButonPin =  2;
void setup(){
  EEPROM.get(0,Alarm);
  lcd.begin(16,2); 
  pinMode(uyariBuzzerPin, OUTPUT);
  pinMode(uyariKirmiziLedPin, OUTPUT);
  pinMode(uyariYesilLedPin, OUTPUT);

  pinMode(kesmeButonPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(kesmeButonPin),&Durdur,RISING);
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()>0){
  	veri = Serial.read();
  }
  if(veri=='1'){
  	Alarm=1;
  }
  if(Alarm==1){
  	lcd.setCursor(0,0);
    lcd.print("  HIRSIZ VAR!   ");
    lcd.setCursor(0,1);
    lcd.print("  EV GUVENSIZ!  ");
    digitalWrite(uyariKirmiziLedPin, HIGH);
    digitalWrite(uyariBuzzerPin, HIGH);
    digitalWrite(uyariYesilLedPin, LOW);


  }
  else{
    lcd.setCursor(0,0);
    lcd.print("   HIRSIZ YOK   ");
    lcd.setCursor(0,1);
    lcd.print("   EV GUVENLI   ");
   	digitalWrite(uyariKirmiziLedPin, LOW);
    digitalWrite(uyariBuzzerPin, LOW);
    digitalWrite(uyariYesilLedPin, HIGH);

  }
  EEPROM.put(0,Alarm);
}
void Durdur(){
  Alarm = 0;
}