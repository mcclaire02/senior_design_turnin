/////////////////////////////////
// ICM20948 9-AXIS IMU LIBRARY //
// DEVELOPED BY SAUCE LABS     //
// VERSION 0.1, 12/6/2023      //
/////////////////////////////////
#pragma once
#include <Wire.h>

class ICM20948 : TwoWire
{
    public:
        enum MODE {_6AXIS,_9AXIS,GYRO_ONLY, ACCEL_ONLY, MAG_ONLY, DMP_ON, DMP_OFF};
        struct IMU_Data {
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
        };
        bool isPresent();
        void setMode(MODE);
        void getAccelData(IMU_Data &);
        void getGyroData(IMU_Data &);
        void getMagData(IMU_Data &);
        void getTempData(IMU_Data &);
    private:
        void wireGetData(uint8_t, uint8_t, uint8_t, uint8_t &);
        uint8_t wireGetByte(uint8_t, uint8_t);
        void wireSendByte(uint8_t, uint8_t, uint8_t);

};