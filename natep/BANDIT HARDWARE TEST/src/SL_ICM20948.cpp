/////////////////////////////////
// ICM20948 9-AXIS IMU LIBRARY //
// DEVELOPED BY SAUCE LABS     //
// VERSION 0.1, 12/6/2023      //
/////////////////////////////////
#include "SL_ICM20948.h"

uint8_t address = 0b01101001; //AD0 is HIGH

void ICM20948::wireGetData(uint8_t addr, uint8_t cmd, uint8_t size, uint8_t &buf)
{
    beginTransmission(addr);
    write(cmd);
    endTransmission();
    
    if(requestFrom(addr, size) == size){
        readBytes(&buf,size);
    } else buf = -1;
}

uint8_t ICM20948::wireGetByte(uint8_t addr, uint8_t cmd)
{
    beginTransmission(addr);
    write(cmd);
    endTransmission();
    if(requestFrom(addr,(uint8_t) 1) == 1){
        return read();
    } else return -1;
}

void ICM20948::wireSendByte(uint8_t addr, uint8_t cmd, uint8_t data)
{
    beginTransmission(addr);
    write(cmd);
    write(data);
    endTransmission();
}

bool ICM20948::isPresent()
{
    return wireGetByte(address, 0) == 234;
}

void ICM20948::setMode(MODE m)
{
    switch(m){
        case _9AXIS:

        case _6AXIS:

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
