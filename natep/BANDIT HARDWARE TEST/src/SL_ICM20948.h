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
        uint8_t Get_Whoami();
    private:
        void Wire_get_data(uint8_t, uint8_t, uint8_t, uint8_t &);
        uint8_t Wire_get_byte(uint8_t, uint8_t);
        void Wire_send_byte(uint8_t, uint8_t, uint8_t);

};