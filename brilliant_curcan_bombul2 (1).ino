#include <SoftwareSerial.h>
int uyariLed1Yesil = 7;
int uyariLed2Kirmizi= 13;


void setup(){
	noInterrupts(); // interrupt kapandı
	TCCR1A = 0;
	TCCR1B = 8 | 4;
	TCNT1  = 0; // Sayacı Sıfırladık
	OCR1A = 6250; //( 16000000/(256*10))  10 Hz Ayarladık
  	TIMSK1 =2 ;
  	interrupts(); // interrupt açıldı
  	Serial.begin(9600); 
  	pinMode(uyariLed2Kirmizi,OUTPUT);
  	pinMode(uyariLed1Yesil,OUTPUT);
}
void loop(){
  delay(10000); 
}


ISR(TIMER1_COMPA_vect){   //timer1 interrupt ı 10Hz de tetikleniyor.
  int deger=analogRead(A0);
  if(deger<333){
  	Serial.print('1');
   	digitalWrite(uyariLed1Yesil,LOW); 
    digitalWrite(uyariLed2Kirmizi,HIGH);
  }
  else{
    Serial.print('0');
    digitalWrite(uyariLed1Yesil,HIGH);
    digitalWrite(uyariLed2Kirmizi,LOW);
  }
}
