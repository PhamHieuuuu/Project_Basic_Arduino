#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <SPI.h>

#define TFT_SCLK  13   // (SCK) cố định
#define TFT_MOSI  11   //(SDA) cố định
#define TFT_RST   A0 //có thể thay đổi
#define TFT_DC    A1  //(RS) có thể thay đổi
#define TFT_CS    A2 //có thể thay đổi

#define TFT_BL    10  // Chân điều khiển đèn nền (nếu có)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


void setup(void) {
  pinMode(TFT_BL, OUTPUT);
  analogWrite(TFT_BL, 155);  // Bật đèn nền

  analogWrite(5, 100);  // Độ sáng khoảng 30% (0 là tắt, 255 là sáng nhất)
  tft.initR(INITR_BLACKTAB);  
  tft.fillScreen(ST7735_BLACK); // Xóa màn hình, đảm bảo nền đen

  // Hiển thị từng dòng với màu khác nhau
  tft.setTextSize(1);

  tft.setCursor(5, 50);
  tft.setTextColor(ST7735_RED);
  tft.println("ESP32 & TFT ST7735");

  tft.setCursor(5, 40);
  tft.setTextColor(ST7735_GREEN);
  tft.println("Day la man hinh TFT");

  tft.setCursor(5, 60);
  tft.setTextColor(ST7735_BLUE);
  tft.println("Dung thu vien Ad");

  tft.setCursor(5, 10);
  tft.setTextColor(ST7735_YELLOW);
  tft.println("Ho tro SPI, do phan giai");

  tft.setCursor(5, 100);
  tft.setTextColor(ST7735_CYAN);
  tft.println("160x128 pixels. 35'C");

}



void loop() {

}
