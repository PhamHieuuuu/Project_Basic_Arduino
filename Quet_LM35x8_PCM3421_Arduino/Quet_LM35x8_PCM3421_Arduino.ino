#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); 

#define MCP3421_ADDRESS 0x68 // Địa chỉ I2C của MCP3421
#define A 2
#define B 3
#define C 4

void setup() {
  for(int i=2;i<5;i++)
  pinMode(i,OUTPUT);

  lcd.init();
  lcd.backlight();

  Wire.begin();             // Khởi tạo I2C ở chế độ Master
  Serial.begin(9600);       
  Serial.println("Dang Doc MCP3421...");
}

void Control(unsigned char X){
	int O1 = X & 0x01;
	int O2 = X & 0x02;
	int O3 = X & 0x04;

  digitalWrite(A,O1);
  digitalWrite(B,O2);
  digitalWrite(C,O3);
}


void loop() {

  for(int i=0;i<8;i++){
  Control(i);
  uint16_t adcValue = readADC(); 
  float Value = (float)adcValue / 1003.0; // Chuyển đổi từ 0-1003 sang 0-1 tức 0-1V
  float temperature = Value * 100.0; // LM35 có tỷ lệ 10mV/°C, nên nhân với 100 để có nhiệt độ

// Hiển thị Serial
  Serial.print("ADC Value "+ String(i+1)+ ": ");
  Serial.println(adcValue);
  Serial.print("Temperature: "+ String(i+1)+ ": ");
  Serial.print(temperature);
  Serial.println("'C");
  Serial.println("");

// Hiển thị LCD 16x4

  int row = i / 2;

  int col;
  if(i%2==0) col=0;
  else col=11;

  lcd.setCursor(col, row); // Đặt con trỏ tại vị trí
  lcd.print("T" + String(i+1) + ":" + String(temperature) + "C");

  lcd.setCursor(10,row);
  lcd.print("|");
  delay(400); 
}
}

// Hàm đọc giá trị ADC từ MCP3421
uint16_t readADC() {

// cần có đoạn này để báo cho slave biết, nếu không vi đk sẽ đọc không kịp gây lỗi dữ liệu
  Wire.beginTransmission(MCP3421_ADDRESS);
  Wire.write(0x00); // Gửi lệnh bắt đầu chuyển đổi (nếu cần thiết)
  Wire.endTransmission();
  delay(100); // Đợi 50ms để quá trình chuyển đổi hoàn tất

  Wire.requestFrom(MCP3421_ADDRESS, 2); // Yêu cầu 2 byte dữ liệu từ MCP3421
  if (Wire.available() == 2) {
    uint8_t highByte = Wire.read(); // Byte cao
    uint8_t lowByte = Wire.read();  // Byte thấp
    return (highByte << 8) | lowByte; // Gộp 2 byte thành giá trị 16-bit (dịch bit cao sang trái 8bit=> phép OR với bit thấp)
  } else {
    Serial.println("Loi doc MCP3421");
    return 0; 
  }
}
