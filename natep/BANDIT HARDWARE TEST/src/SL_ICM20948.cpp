/////////////////////////////////
// ICM20948 9-AXIS IMU LIBRARY //
// DEVELOPED BY SAUCE LABS     //
// VERSION 0.1, 12/6/2023      //
/////////////////////////////////
#include "SL_ICM20948.h"

uint8_t address = 0b01101001; //AD0 is HIGH
TwoWire& TW = Wire;

ICM20948::ICM20948(uint8_t bus)
{
    if(bus == 1) TW = Wire1;
}

uint8_t ICM20948::wireGetByte(uint8_t addr, uint8_t cmd)
{
    TW.beginTransmission(addr);
    TW.write(cmd);
    TW.endTransmission();
    if(TW.requestFrom(addr,(uint8_t) 1) == 1){
        return TW.read();
    } else return -1;
}

void ICM20948::wireGetData(uint8_t addr, uint8_t cmd, uint8_t size, uint8_t &buf)
{
    TW.beginTransmission(addr);
    TW.write(cmd);
    TW.endTransmission();
    
    if(TW.requestFrom(addr, size) == size){
        TW.readBytes(&buf,size);
    } else buf = -1;
}

void ICM20948::wireSendByte(uint8_t addr, uint8_t cmd, uint8_t data)
{
    TW.beginTransmission(addr);
    TW.write(cmd);
    TW.write(data);
    TW.endTransmission();
}

bool ICM20948::isPresent()
{
    return wireGetByte(address, 0) == (uint8_t) 234;
}

void ICM20948::setMode(MODE m)
{
    switch(m){
        case _9AXIS:
            //TODO: Set up 9 Axis
            break;
        case _6AXIS:
            //TODO: Set up 6 axis 
            break;
        case GYRO_ONLY:

            break;
        case ACCEL_ONLY:
            
            break;
        case MAG_ONLY:

            break;
        case DMP_OFF:

            break;
        case DMP_ON:

            break;
        default:
            break;
    }
}

void ICM20948::getAccelData(IMU_Data &)
{

}

void ICM20948::getGyroData(IMU_Data &)
{

}

void ICM20948::getMagData(IMU_Data &)
{

}

void ICM20948::getTempData(IMU_Data &)
{

}

ICM20948 IMU = ICM20948(0);
ICM20948 IMU1 = ICM20948(1);
