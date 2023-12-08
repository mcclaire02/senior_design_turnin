/////////////////////////////////
// ICM20948 9-AXIS IMU LIBRARY //
// DEVELOPED BY SAUCE LABS     //
// VERSION 0.1, 12/6/2023      //
/////////////////////////////////
#ifndef SL_ICM20948_H
#define SL_ICM20948_H
#include <Wire.h>

typedef struct IMU_Data {
    float acc_x;
    float acc_y;
    float acc_z;

    float gy_x;
    float gy_y;
    float gy_z;

    float mag_x;
    float mag_y;
    float mag_z;

    float temperature;
} IMUData; //don't instantiate one, just used the buffer passed in.

enum MODE {_6AXIS,_9AXIS,GYRO_ONLY, ACCEL_ONLY, MAG_ONLY, DMP_ON, DMP_OFF};


class ICM20948
{
    public:
        ICM20948(uint8_t);
        

        bool isPresent();
        void setMode(MODE);
        void getAccelData(IMU_Data &);
        void getGyroData(IMU_Data &);
        void getMagData(IMU_Data &);
        void getTempData(IMU_Data &);
        void getAllData(IMU_Data &);
        void getConfig();
    private:
        struct Sensor_Config{
            uint8_t ACCEL_SENSITIVITY = 0;
            uint8_t GYRO_SENSITIVITY = 0;

        } config;
        void getData(uint8_t, uint8_t, uint8_t &);
        uint8_t getByte(uint8_t);
        void sendByte(uint8_t, uint8_t);
};

extern ICM20948 IMU;
extern ICM20948 IMU1;

#endif