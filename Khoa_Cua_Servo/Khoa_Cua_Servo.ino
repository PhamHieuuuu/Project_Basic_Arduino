#include "Servo.h"
Servo dc;
#include "Keypad.h"
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); // Khởi tạo LCD với địa chỉ I2C 0x27, kích thước 16x2
byte colpin[4] = {2, 3, 4, 5}; // Chân kết nối cột của keypad
byte rowpin[4] = {6, 7, 8, 9}; // Chân kết nối hàng của keypad
char keys[4][4] = { // Mảng ký tự của keypad
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
char matkhau[] = {'4', '4', '4', '4'}; // Mật khẩu gốc
char nhap[4]; // Mảng lưu trữ các ký tự nhập vào
int viTri = 0; // Biến đếm vị trí nhập ký tự
Keypad kytu = Keypad(makeKeymap(keys), rowpin, colpin, 4, 4); // Khởi tạo keypad

void setup() {
  Serial.begin(9600);
  dc.attach(10); // Gán servo vào chân 10
  lcd.init();
  lcd.backlight();
  pinMode(11, OUTPUT); // Chân LED đỏ
  pinMode(12, OUTPUT); // Chân LED xanh
  pinMode(13,OUTPUT);
  dc.write(0);
}

void coi(int h){
 for(int i=0;i<h;i++){
  digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13,LOW);}
}
void key44() {
  char giatri = kytu.getKey(); // Đọc giá trị từ keypad
  lcd.setCursor(0, 0);
  lcd.print("Nhap MK|DoiMK(D)");

  if (giatri) { // Nếu nhấn phím
   coi(1);
    lcd.setCursor(viTri + 7, 1);
    lcd.print(giatri);   
    nhap[viTri] = giatri;
    viTri++;
    delay(300);

    if (viTri == 4) { // Nếu nhập đủ 4 ký tự
      if (nhap[0] == matkhau[0] && nhap[1] == matkhau[1] && nhap[2] == matkhau[2] && nhap[3] == matkhau[3]) { // Kiểm tra mật khẩu
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Mat Khau Dung");
        dc.write(180); // Mở cửa
       coi(5);
        digitalWrite(12, HIGH); // Bật đèn xanh
        delay(3000);
        digitalWrite(12, LOW); // Tắt đèn xanh
        dc.write(0);
        lcd.clear();
        viTri = 0;
      } else {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Sai Mat Khau");
         coi(5);
        digitalWrite(11, HIGH); // Bật đèn đỏ
        delay(2000);
        digitalWrite(11, LOW); // Tắt đèn đỏ
        viTri = 0;
      }
    }

    if (giatri == 'D' && viTri == 1) { // Nếu nhấn phím 'D' để đổi mật khẩu
      viTri = 0;
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Nhap Mat Khau");
      while (viTri < 4) {
        char mk = kytu.getKey();
        if (mk) {
           coi(1);
          lcd.setCursor(viTri + 7, 1);
          lcd.print('*'); // Hiển thị ký tự *
          nhap[viTri] = mk;
          viTri++;
          delay(300);
        }
      }
      if (nhap[0] == matkhau[0] && nhap[1] == matkhau[1] && nhap[2] == matkhau[2] && nhap[3] == matkhau[3]) {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Mat Khau Dung");
         coi(5);
        digitalWrite(12, HIGH); // Bật đèn xanh
        delay(3000);
        digitalWrite(12, LOW); // Tắt đèn xanh
        lcd.clear();
        viTri = 0;
        lcd.setCursor(2, 0);
        lcd.print("Nhap Key Moi");
        for (int i = 0; i < 4; i++) {
          while (true) {
            char chon = kytu.getKey();
            if (chon) {
               coi(1);
              lcd.setCursor(i + 7, 1);
              lcd.print('*'); 
              delay(300);// Hiển thị ký tự *
              matkhau[i] = chon; // Cập nhật mật khẩu mới
              break;
            }
          }
        }
        lcd.clear();
        lcd.setCursor(3, 0);
         coi(3);
        lcd.print("Thanh Cong");
        delay(2000);
        viTri = 0;
      } else {
        lcd.clear();
        lcd.setCursor(1, 0);
         coi(3);
        lcd.print("Sai Mat Khau");
        delay(2000);
        viTri = 0;
      }
    }
  }
}

void loop() {
  key44();
 
}
