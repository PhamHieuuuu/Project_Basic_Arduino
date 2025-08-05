const int trig=8;
const int echo=7;
unsigned long thoigian;
int khoangcach;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// sda a4

void setup() {
 Serial.begin(9600);
 pinMode(trig,OUTPUT);
 pinMode(echo,INPUT);

 lcd.init();
lcd.backlight();

lcd.setCursor(0,0);
 lcd.print("Khoang cach: ");


}

void loop() {
  digitalWrite(trig,0);
  delayMicroseconds(2);
   digitalWrite(trig,1);
delayMicroseconds(10);
   digitalWrite(trig,0);

thoigian = pulseIn(echo, HIGH);

khoangcach= int (thoigian /2/29.412); // thuật toán
// thời gian/2 lấy thời gian 1 chiều 
// chia cho 29.412 là thuật toán đổi từ thời gian(microsecond) sang khoảng cách (cm)

// in ra lcd
if(khoangcach>=0&&khoangcach<=9){
lcd.setCursor(9,1);
 lcd.print(khoangcach);
 lcd.setCursor(10,1);
  lcd.print("cm     ");
  delay(100);}
else if(khoangcach>=10&&khoangcach<=99){
 lcd.setCursor(9,1);
 lcd.print(khoangcach);
 lcd.setCursor(11,1);
  lcd.print("cm      ");
  delay(100); }
else if(khoangcach>=100&&khoangcach<=999){
   lcd.setCursor(9,1);
 lcd.print(khoangcach);
 lcd.setCursor(12,1);
  lcd.print("cm     ");
  delay(100);
}
else if(khoangcach>=1000&&khoangcach<=9999){
   lcd.setCursor(9,1);
 lcd.print(khoangcach);
 lcd.setCursor(13,1);
  lcd.print("cm");
  delay(100);
}

// inm ra serial
Serial.print("khoảng cách là: ");
Serial.print(khoangcach);
Serial.println("cm");


}
