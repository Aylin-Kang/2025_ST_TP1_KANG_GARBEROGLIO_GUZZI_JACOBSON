//Garberoglio, Guzzi, Jacobson, Kang

#include <DHT.h>
#include <DHT_U.h>
#include <U8g2lib.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);


#define P1       0
#define ESPERA1  1
#define P2       2
#define ESPERA2  3
#define SUMA     4
#define RESTA    5



int estadoActual = P1;


float TA = 0;
float TU = 22;



#define SW1 34
#define SW2 35
#define LED 25

#define DHTPIN 23
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

char stringtemp[10]; 
char stringumbral[10];

void setup() {
Serial.begin(115200);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(LED, OUTPUT);
 u8g2.begin();
dht.begin();
}




void loop() {
  switch (estadoActual) {

    case P1:{
      getTemp();
      printTemp1();
      if (TA > TU) {
        digitalWrite(LED,HIGH);
      } else 
      if (TA < TU) {
        digitalWrite(LED,LOW);
      }
      
      if (digitalRead(SW1) == LOW && digitalRead(SW2) == LOW) {
        estadoActual = ESPERA1;
      }
    }
    break;

    case ESPERA1:{
      if (digitalRead(SW1) == HIGH && digitalRead(SW2) == HIGH) {
        estadoActual = P2;
      }
    }break;




    case P2:{
      printTemp2();
      if (digitalRead(SW1) == LOW) {
        estadoActual = SUMA;
      } else if (digitalRead(SW2) == LOW) {
        estadoActual = RESTA;
      }
    }break;


    case SUMA:{
      if (digitalRead(SW1) == HIGH) {
        TU += 1;
        estadoActual = P2;
      } else if (digitalRead(SW2) == LOW && digitalRead(SW1) == LOW) {
        estadoActual = ESPERA2;
      }
    }break;




    case RESTA:{
      if (digitalRead(SW2) == HIGH) {
        TU -= 1;
        estadoActual = P2;
      } else if (digitalRead(SW1) == LOW && digitalRead(SW2) == LOW) {
        estadoActual = ESPERA2;
      }
    }break;
    
    case ESPERA2:
    {
      if (digitalRead(SW1) == HIGH && digitalRead(SW2) == HIGH) {
        estadoActual = P1;
      }
    }
    break;
  }

}


void getTemp() {
    //TA = dht.readTemperature();
    TA = 25;
}
void printTemp1(void)
{ 
    u8g2.clearBuffer();         
    u8g2.setFont(u8g2_font_ncenB14_tr); 
    u8g2.drawStr(0,30,"T: "); 
    sprintf (stringtemp, "%f" , TA); 
    u8g2.drawStr(27,30,stringtemp);
    u8g2.drawStr(80,30,"C");
    u8g2.drawStr(0,60,"U: "); 
    sprintf (stringumbral, "%f" , TU); 
    u8g2.drawStr(27,60,stringumbral);
    u8g2.drawStr(80,60,"C");
    u8g2.sendBuffer();      
  }




void printTemp2(void)
{ 
    u8g2.clearBuffer();         
    u8g2.setFont(u8g2_font_ncenB14_tr); 
    u8g2.drawStr(0,60,"U: "); 
    sprintf (stringumbral, "%f" , TU); 
    u8g2.drawStr(27,60,stringumbral);
    u8g2.drawStr(80,60,"C");
    u8g2.sendBuffer();         
}
