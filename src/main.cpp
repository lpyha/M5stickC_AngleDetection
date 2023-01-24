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
  M5.IMU.Init();
  M5.Lcd.setRotation(3);
}

void loop() {
  M5.Lcd.fillScreen(BLACK);
  M5.IMU.getAccelData(&accX,&accY,&accZ);
  //範囲π>-πまで
  theta = atan2(accY, accX);
  theta -= PI;
  theta = abs(theta);
  degree = theta * (180 / PI);
  Serial.println(degree);
  M5.Lcd.setCursor(40, 30);
  M5.Lcd.setTextSize(5);
  M5.Lcd.printf("%d", degree);
  delay(100);
}
