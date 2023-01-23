#include <M5StickC.h>

float accX;
float accY;
float accZ;
float theta;
int degree;  
void setup() {
  accX = 0.0F;
  accY = 0.0F;
  accZ = 0.0F;
  theta = 0.0F;
  degree = 0;
  M5.begin();
  Serial.begin(9600);
  M5.IMU.Init();
  M5.Lcd.setRotation(3);
}

void loop() {
  M5.Lcd.fillScreen(BLACK);
  M5.IMU.getAccelData(&accX,&accY,&accZ);
  theta = atan2(accY, accX);
  degree = theta * (180 / PI);
  Serial.println(degree);
  //M5.Lcd.setCursor(5, 20);
  //M5.Lcd.printf("X> %5.2f  Y> %5.2f G\n\n\n\n", accX, accY);
  M5.Lcd.setCursor(45, 35);
  M5.Lcd.setTextSize(6);
  M5.Lcd.printf("%d", degree);
  delay(100);
}
