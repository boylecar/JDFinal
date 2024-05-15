// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <string.h>
#include <SoftwareSerial.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"

Adafruit_MPU6050 mpu;
SoftwareSerial BTSerial(5, 6);   // RX | TX

String messageBuffer = "";
String message = "";

void mpu_setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}

void screen_ex(void) {
  Paint_SetRotate(ROTATE_180);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 90, WHITE);
  Paint_Clear(WHITE);
  Paint_DrawString_EN(30, 10, "123", &Font24, YELLOW, RED);
  Paint_DrawString_EN(30, 34, "ABC", &Font24, BLUE, CYAN);


  
  Paint_DrawRectangle(125, 10, 225, 58, RED,  DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
  Paint_DrawLine(125, 10, 225, 58, MAGENTA,   DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  Paint_DrawLine(225, 10, 125, 58, MAGENTA,   DOT_PIXEL_2X2,LINE_STYLE_SOLID);

  Paint_DrawCircle(150,100, 25, BLUE,   DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  Paint_DrawCircle(180,100, 25, BLACK,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  Paint_DrawCircle(210,100, 25, RED,    DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  Paint_DrawCircle(165,125, 25, YELLOW, DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  Paint_DrawCircle(195,125, 25, GREEN,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  
  

  Paint_DrawImage(gImage_70X70, 20, 80, 70, 70); 
  Paint_DrawFloatNum (5, 150 ,987.654321,6,  &Font20,    WHITE,   LIGHTGREEN);

}

void screen_setup(void) {
  Config_Init();
  LCD_Init();
  LCD_Clear(0xffff);
}

void acc_print(sensors_event_t* a, sensors_event_t* g, sensors_event_t* temp) {
  /* Get new sensor events with the readings */
  
  Serial.print("Acceleration X: ");
  Serial.print(a->acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a->acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a->acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g->gyro.x);
  Serial.print(", Y: ");
  Serial.print(g->gyro.y);
  Serial.print(", Z: ");
  Serial.print(g->gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp->temperature);
  Serial.println(" degC");

  Serial.println("");
}

void BT_setup1(void) {
  pinMode(4, OUTPUT);    /* this pin will pull the HC-05 pin 34 (KEY pin) HIGH to switch module to AT mode */
  digitalWrite(4, HIGH);
//  pinMode(10, INPUT);
//  pinMode(11, OUTPUT);
  
}

void BT_setup2(void) {
  Serial.begin(9600);
  Serial.println("Enter AT Commands:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command mode
}

void setup(void) {
////////////////////////// FOR ACC AND SCREEN ////////////////////////
  screen_setup();
//    //screen_ex();
  Paint_SetRotate(ROTATE_180);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 90, WHITE);
  Paint_DrawString_EN(5, 34, "z", &Font24, BLUE, CYAN);
  Paint_DrawString_EN(5, 68, "y", &Font24, BLUE, CYAN);
  Paint_DrawString_EN(5, 102, "x", &Font24, BLUE, CYAN);
  
  mpu_setup();
////////////////////////////////////////////////////////////////////////

//////////////////////////// FOR BLUETOOTH /////////////////////////////
//  BT_setup1();
//  BT_setup2();
////////////////////////////////////////////////////////////////////////
}

void loop() {

////////////////////////// FOR ACC AND SCREEN ////////////////////////
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  //acc_print(&a, &g, &temp);

  float az = a.acceleration.z;
  float ay = a.acceleration.y;
  float ax = a.acceleration.x;
  String strz = String(az);
  String stry = String(ay);
  String strx = String(ax);
  char charArrayz[strz.length() + 1]; // +1 for the null terminator
  char charArrayy[stry.length() + 1];
  char charArrayx[strx.length() + 1];
  strz.toCharArray(charArrayz, sizeof(charArrayz));
  stry.toCharArray(charArrayy, sizeof(charArrayy));
  strx.toCharArray(charArrayx, sizeof(charArrayx));  
  
  Paint_SetRotate(ROTATE_180);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 90, WHITE);
  Paint_DrawString_EN(30, 34, charArrayz, &Font24, BLUE, CYAN);
  Paint_DrawString_EN(30, 68, charArrayy, &Font24, BLUE, CYAN);
  Paint_DrawString_EN(30, 102, charArrayx, &Font24, BLUE, CYAN);
////////////////////////////////////////////////////////////////////////

//////////////////////////// FOR BLUETOOTH //////////////////////////////////
//  if (Serial.available())           // Keep reading from Arduino Serial Monitor
//      BTSerial.write(Serial.read());  // and send to HC-05
// 
//    //The code below allows for commands and messages to be sent from HC-05 -> COMPUTER (serial monitor)
//  if (BTSerial.available())         // Keep reading from HC-05 and send to Arduino
//      Serial.write(BTSerial.read());  // Serial Monitor
//////////////////////////////////////////////////////////////////////////////
}
