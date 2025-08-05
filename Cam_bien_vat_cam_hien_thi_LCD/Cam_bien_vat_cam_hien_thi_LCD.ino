// A5-SCL  A4-SDA của I2C
// chân 2 đọc cảm biến

#include"Wire.h"
#include"LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd (0x27,16,2);
  int dem=0;
  int h=1;

int cambien=2;
void setup() {
 pinMode(2,INPUT);
 lcd.init();
lcd.backlight();

// tạo tiêu đề
//   Trang thai | SL
//      NO        0
 lcd.setCursor(0,0);
  lcd.print("Trang thai|");
   lcd.setCursor(11,0);
  lcd.print("SoLan");
  lcd.setCursor(10,1);
  lcd.print("|");

 lcd.setCursor(0,1);
  lcd.print("    NO   ");
lcd.setCursor(13,1);
  lcd.print("0");
}
 

void doccambien(){
int Doc=digitalRead(cambien);
if(Doc==0&&h==1){
  dem=dem+1;
   lcd.setCursor(0,1);
  lcd.print("Co Vat Can");
lcd.setCursor(13,1);
  lcd.print(dem);
  delay(100);
 h=0;}
 else if(Doc==1&&h==0){
  lcd.setCursor(0,1);
  lcd.print("    NO    ");
  h=1;
 }
}

void loop() {
doccambien();
}



