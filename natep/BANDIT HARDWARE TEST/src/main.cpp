/////////////////////////////////////
// BANDIT FIRMWARE VERSION 0.1     //
// DEVELOPED BY NATHAN PENDERGRAST //
// DEVELOPED BY MARY CLAIRE CORELL //
// DEVELOPED BY NATHAN DINH        //
/////////////////////////////////////

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_SSD1351.h>
#include "image.h"
#include "SL_ICM20948.h"

// CONSTANTS
#define OLED_RESET  7
#define OLED_CS     15
#define OLED_DIN    16
#define OLED_CLK    17
#define OLED_DC     18

#define I2C_SDA     6
#define I2C_SCL     5
IMUData imu_data;
//I2C Addresses
uint8_t icm20948 = 0b1101001;
uint8_t max1704x = 0b0110010; //OK. so the datasheet has the wrong value, it's correct here.(0x32)

#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

Adafruit_SSD1351 display = Adafruit_SSD1351(128, 128,OLED_CS,OLED_DC,OLED_DIN,OLED_CLK,OLED_RESET);
uint8_t temp;

int pos = 0;
void setup() {
    Serial0.begin(115200);
    Wire.begin(I2C_SDA,I2C_SCL);

    //IMU.reset();
    IMU.init();

    display.begin(0U);
    display.setRotation(2);
    display.fillScreen(WHITE);
    delay(2000);
    display.fillScreen(BLACK);

    display.drawRGBBitmap(0,0,*saucelogo_rgb,128,128);
    delay(200);
    display.fillScreen(BLACK);
    delay(200);
    // if(IMU.isPresent()) {
    //     display.println("ICM20948 Present");
    //     Serial0.println("ICM20948 Present");
    // }
    //IMU.getConfig();
    //Wire_get_byte(max1704x,9, temp);
    //Serial0.println(temp);
    // if(temp == 3){
    //     display.println("MAX17044 is present!");
    //     Serial0.println("MAX17044 is present!");
    // }
    // for(uint8_t i = 0; i < 255;i++){
    //     Wire_get_byte(max1704x,i, temp);
    //     Serial0.printf("0x%02x: %d\n", i, temp);
    // }

    display.fillScreen(BLACK);
    display.setTextColor(WHITE);
    display.setCursor(0,0);

    delay(300);
}

void loop() {
    // display.setTextColor(WHITE);
    // display.setCursor(0,0);
    // //Wire_get_byte(max1704x,4, temp);
    // display.printf("%03d%",temp);
    // delay(2000);
    // display.setTextColor(BLACK);
    // display.setCursor(0,0);
    // display.printf("%03d%",temp);
    // delay(5);
    IMU.getAccelData(imu_data);
    IMU.getGyroData(imu_data);
    display.printf("A:X:%1.2fY:%1.2fZ:%1.2f", imu_data.acc_x, imu_data.acc_y, imu_data.acc_z);
    display.printf("G:X:%1.2fY:%1.2fZ:%1.2f", imu_data.gy_x, imu_data.gy_y, imu_data.gy_z);
    delay(100);
    display.fillRect(0,0,128,25,BLACK);
    display.setCursor(0,0);
}