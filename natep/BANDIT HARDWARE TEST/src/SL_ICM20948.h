/////////////////////////////////
// ICM20948 9-AXIS IMU LIBRARY //
// DEVELOPED BY SAUCE LABS     //
// VERSION 0.1, 12/6/2023      //
/////////////////////////////////
#ifndef SL_ICM20948_H
#define SL_ICM20948_H
#include <Wire.h>

#define WHOAMI          0x00

#define REG_BANK_SEL    0x7F
#define USR_BANK_0      (uint8_t)(0x00 << 4)
#define USR_BANK_1      (uint8_t)(0x01 << 4)
#define USR_BANK_2      (uint8_t)(0x02 << 4)
#define USR_BANK_3      (uint8_t)(0x03 << 4)

#define USER_CTRL       0x03
#define PWR_MGMT_1      0x06
#define PWR_MGMT_2      0X07

typedef struct IMU_Data {
    float acc_x;
    float acc_y;
    float acc_z;

    float gy_x;
    float gy_y;
    float gy_z;

    int16_t mag_x;
    int16_t mag_y;
    int16_t mag_z;

    int16_t temperature;
} IMUData; //don't instantiate one, just used the buffer passed in.

enum MODE {_6AXIS,_9AXIS,GYRO_ONLY, ACCEL_ONLY, MAG_ONLY, DMP_ON, DMP_OFF};


class ICM20948
{
    public:
        ICM20948(uint8_t);

        bool init();
        void reset();
        void setMode(MODE);
        void getAccelData(IMU_Data &);
        void getGyroData(IMU_Data &);
        void getMagData(IMU_Data &);
        void getTempData(IMU_Data &);
        void getAllData(IMU_Data &);
        bool isPresent();
        void getConfig();
    private:
        uint8_t currentBank;
        void setBank(uint8_t);
        struct Sensor_Config{
            uint16_t ACCEL_SENSITIVITY;
            float GYRO_SENSITIVITY;
            MODE mode;
        } config;
        void getData(uint8_t, uint8_t, uint8_t &);
        uint8_t getByte(uint8_t);
        void sendByte(uint8_t, uint8_t);
};

extern ICM20948 IMU;
extern ICM20948 IMU1;

#endif