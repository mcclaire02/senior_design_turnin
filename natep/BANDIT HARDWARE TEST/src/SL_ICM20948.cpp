/////////////////////////////////
// ICM20948 9-AXIS IMU LIBRARY //
// DEVELOPED BY SAUCE LABS     //
// VERSION 0.1, 12/6/2023      //
/////////////////////////////////
#include "SL_ICM20948.h"

uint8_t address = 0b01101001; //AD0 is HIGH
#define ALT_ADDRESS = 0h68;     //AD0 is LOW

void ICM20948::Wire_get_data(uint8_t addr, uint8_t cmd, uint8_t size, uint8_t &buf)
{
    Wire.beginTransmission(addr);
    Wire.write(cmd);
    Wire.endTransmission();
    
    if(Wire.requestFrom(addr, size) == size){
        Wire.readBytes(&buf,size);
    } else buf = -1;
}

uint8_t ICM20948::Wire_get_byte(uint8_t addr, uint8_t cmd)
{
    Wire.beginTransmission(addr);
    Wire.write(cmd);
    Wire.endTransmission();
    if(Wire.requestFrom(addr,(uint8_t) 1) == 1){
        return Wire.read();
    } else return -1;
}

void ICM20948::Wire_send_byte(uint8_t addr, uint8_t cmd, uint8_t data)
{
    Wire.beginTransmission(addr);
    Wire.write(cmd);
    Wire.write(data);
    Wire.endTransmission();
}

uint8_t ICM20948::Get_Whoami()
{
    return Wire_get_byte(address, 0);
}

