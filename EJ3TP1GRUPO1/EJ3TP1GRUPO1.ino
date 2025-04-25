//Garberoglio, Guzzi, Jacobson, Kang

#include <DHT.h>
#include <DHT_U.h>
#include <U8g2lib.h>

/* ----------------------------------------------------------------------------------------------------- */

// Definicion de constructores y variables globales

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

/* ----------------------------------------------------------------------------------------------------- */
void  printBMP_OLED(void );

#define DHTPIN 23
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float TU = 28;

void setup() 
{
  Serial.begin(9600);
  Serial.println(F("OLED test"));
  u8g2.begin();
  dht.begin();
}
  
void loop() 
{
 printBMP_OLED();
    delay(2000);
}

void printBMP_OLED(void)
{  
    float temp = dht.readTemperature();
    char stringtemp[5];
    u8g2.clearBuffer();          // clear the internal memory
    if(temp>TU){
      digitalWrite(LED,HIGH);
    }
    else{
      digitalWrite(LED,LOW);
    }
    u8g2.setFont(u8g2_font_ncenB14_tr); // choose a suitable font
    u8g2.drawStr(0,30,"T: ");  // write something to the internal memory
    u8g2.drawStr(27,30,stringtemp);
    u8g2.drawStr(80,30,"C");
    u8g2.sendBuffer();          // transfer internal memory to the display

}
