/////////////////////////////////
// ICM20948 9-AXIS IMU LIBRARY //
// DEVELOPED BY SAUCE LABS     //
// VERSION 0.1, 12/6/2023      //
/////////////////////////////////
#include "SL_ICM20948.h"

uint8_t address = 0b01101001; //AD0 is HIGH
TwoWire& TW = Wire;

#define WHOAMI 0
#define REG_BANK_SEL 127
ICM20948::ICM20948(uint8_t bus)
{
    if(bus == 1) TW = Wire1;
}

uint8_t ICM20948::getByte(uint8_t cmd)
{
    TW.beginTransmission(address);
    TW.write(cmd);
    TW.endTransmission();
    if(TW.requestFrom(address,(uint8_t) 1) == 1){
        return TW.read();
    } else return -1;
}

void ICM20948::getData(uint8_t cmd, uint8_t size, uint8_t &buf)
{
    TW.beginTransmission(address);
    TW.write(cmd);
    TW.endTransmission();
    
    if(TW.requestFrom(address, size) == size){
        TW.readBytes(&buf,size);
    } else buf = -1;
}

void ICM20948::sendByte(uint8_t cmd, uint8_t data)
{
    TW.beginTransmission(address);
    TW.write(cmd);
    TW.write(data);
    TW.endTransmission();
}

bool ICM20948::isPresent()
{
    return getByte(WHOAMI) == (uint8_t) 234;
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
        default: //TODO: Configure default to be 9 Axis mode
            break;
    }
}

void ICM20948::getAccelData(IMU_Data &buf)
{
    uint16_t temp[3] = {0};
    getData(45,6, *(uint8_t*) temp);
    buf.acc_x = (float)temp[0] / config.ACCEL_SENSITIVITY;
    buf.acc_y = (float)temp[1] / config.ACCEL_SENSITIVITY;
    buf.acc_z = (float)temp[0] / config.ACCEL_SENSITIVITY;
}

void ICM20948::getGyroData(IMU_Data &buf)
{

}

void ICM20948::getMagData(IMU_Data &buf)
{

}

void ICM20948::getTempData(IMU_Data &buf)
{

}

void ICM20948::getConfig()
{
    sendByte(REG_BANK_SEL, 2);              //change to USR Bank 2
    uint8_t conf = getByte(20);             //request Accel config1 register
    uint8_t fs = (conf & 0b00000110) >> 1;  //grabs the fs data
    switch(fs){
        case 0://+-2g
            config.ACCEL_SENSITIVITY = 4;
            break;
        case 1://+-4g
            config.ACCEL_SENSITIVITY = 8;
            break;
        case 2://+-8g
            config.ACCEL_SENSITIVITY = 16;
            break;
        case 3://+-16g
            config.ACCEL_SENSITIVITY = 32;
            break;
        default:
            config.ACCEL_SENSITIVITY = 4;
            break;
    }

}

ICM20948 IMU = ICM20948(0);
ICM20948 IMU1 = ICM20948(1);
