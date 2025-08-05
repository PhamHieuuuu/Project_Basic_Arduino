// chân ina,inb điều kiển chiều quay dc 1
// chân inc,ind điều kiển chiều quay dc 2
// OUTA,OUTB chân đấu với đc 1
// OUTC,OUTD chân đấu với đc 2
int inc = 5; // chiều kim đồng hồ
int ind = 6;// ngược kim đồng hồ

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 255; i=i+15) {
    analogWrite(inc, i); 
    delay(1000); // Dừng 1 giây để thấy sự thay đổi tốc độ
  }
   digitalWrite(inc, LOW);  // tắt
delay(3000);
// đảo chiều động cơ
for (int i = 0; i <= 255; i=i+15) {
    analogWrite(ind, i); 
    delay(1000);}
    digitalWrite(ind,LOW);
    delay(3000);

}
