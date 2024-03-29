#include <M5StickC.h>
#include <BluetoothSerial.h>

#define RIGHT 3
#define LEFT 1
#define TOP 0
#define BOTTOM 2

BluetoothSerial SerialBT;

typedef struct{
  float x;
  float y;
  float z;
}accel;
accel acc;

float theta;
int degree;
int lcd_rot;

int AccToDegeree(accel acc){
  //atan2の範囲はπ>-πまで
  theta = atan2(acc.y, acc.x);
  theta -= PI;
  theta = abs(theta);
  degree = theta * (180 / PI);
  return degree;
}


void LcdRotation(int degree){
  if (degree < 45 && degree >= 0 || degree < 360 && degree >= 315){
    M5.Lcd.setCursor(40, 30);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setRotation(RIGHT);
  }else if (degree < 135 && degree >= 45){
    M5.Lcd.setCursor(25, 35);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setRotation(TOP);
  }else if(degree < 225 && degree >= 135){
    M5.Lcd.setCursor(40, 30);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setRotation(LEFT);
  }else if(degree < 315 && degree >= 225){
    M5.Lcd.setCursor(25, 35);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setRotation(BOTTOM);
  }
}

void setup() {
  SerialBT.begin("M5IMU");
  SerialBT.println("START");
  acc.x = 0.0F;
  acc.y = 0.0F;
  acc.z = 0.0F;
  theta = 0.0F;
  degree = 0;
  lcd_rot = 3;
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.setRotation(RIGHT);
  delay(3000);
}

void loop() {
  M5.Lcd.fillScreen(BLACK);
  M5.IMU.getAccelData(&acc.x, &acc.y, &acc.z);
  degree = AccToDegeree(acc);
  LcdRotation(degree);
  M5.Lcd.printf("%d", degree);
  SerialBT.println(degree);
  delay(200);
}
