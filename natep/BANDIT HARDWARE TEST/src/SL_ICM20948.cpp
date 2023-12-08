/////////////////////////////////
// ICM20948 9-AXIS IMU LIBRARY //
// DEVELOPED BY SAUCE LABS     //
// VERSION 0.1, 12/6/2023      //
/////////////////////////////////
#include "SL_ICM20948.h"

uint8_t address = 0b1101001; //AD0 is HIGH
TwoWire& TW = Wire;

ICM20948::ICM20948(uint8_t bus)
{
    if(bus == 1) TW = Wire1;
}

bool ICM20948::init()
{
    TW.flush();
    setBank(USR_BANK_0);
    sendByte(PWR_MGMT_1, 1);
    sendByte(PWR_MGMT_2, 0);
    config.mode = _6AXIS;
    getConfig();
    return true;
}

void ICM20948::reset()
{
    sendByte(PWR_MGMT_1, 0x80);
    init();
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

void ICM20948::setBank(uint8_t bank)
{
    if(currentBank == bank) return;
    sendByte(REG_BANK_SEL, bank);
    currentBank = bank;
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
    setBank(USR_BANK_0);
    return getByte(WHOAMI) == 234;
}

void ICM20948::setMode(MODE m)
{
    config.mode = m;
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
    int16_t data[3] = {0};
    setBank(USR_BANK_0);
    getData(45,6,*(uint8_t*) data);

    buf.acc_x = (float)data[0] / config.ACCEL_SENSITIVITY;
    buf.acc_y = (float)data[1] / config.ACCEL_SENSITIVITY;
    buf.acc_z = (float)data[2] / config.ACCEL_SENSITIVITY;
}

void ICM20948::getGyroData(IMU_Data &buf)
{
    int16_t data[3] = {0};
    setBank(USR_BANK_0);
    getData(51,6,*(uint8_t*) data); //hehe fucky quake III bit hack go brrrr

    buf.gy_x = data[0] / config.GYRO_SENSITIVITY;
    buf.gy_y = data[1] / config.GYRO_SENSITIVITY;
    buf.gy_z = data[2] / config.GYRO_SENSITIVITY;
}

void ICM20948::getMagData(IMU_Data &buf)
{

}

void ICM20948::getTempData(IMU_Data &buf)
{

}

void ICM20948::getConfig()
{
    setBank(USR_BANK_2);             //change to User Bank 2
    uint8_t conf = getByte(20);                     //request Accel config1 register
    uint8_t fs = (conf & 0b00000110) >> 1;          //grabs the fs data
    switch(fs){
        case 0://+-2g
            config.ACCEL_SENSITIVITY = 16384;
            break;
        case 1://+-4g
            config.ACCEL_SENSITIVITY = 8192;
            break;
        case 2://+-8g
            config.ACCEL_SENSITIVITY = 4096;
            break;
        case 3://+-16g
            config.ACCEL_SENSITIVITY = 2048;
            break;
        default://+-2g
            config.ACCEL_SENSITIVITY = 16384;
            break;
    }
    conf = getByte(1);
    fs = (conf & 0b00000110) >> 1;
    switch(fs){
        case 0://+-250dps
            config.GYRO_SENSITIVITY = 131;
            break;
        case 1://+-500dps
            config.GYRO_SENSITIVITY = 65.5;
            break;
        case 2://+-1000pds
            config.GYRO_SENSITIVITY = 32.8;
            break;
        case 3://+-2000dps
            config.GYRO_SENSITIVITY = 16.4;
            break;
        default://+-250dps
            config.GYRO_SENSITIVITY = 131;
            break;
    }
}
ICM20948 IMU = ICM20948(0);
ICM20948 IMU1 = ICM20948(1);
