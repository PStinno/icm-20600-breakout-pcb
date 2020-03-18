#include "Arduino.h"
#include <Wire.h>

#include "ICM_20600.h"

ICM_20600::ICM_20600(void) {}

bool ICM_20600::init(uint8_t addr) {
  // Assign instance address
  i2c_addr = addr;
  // Start i2c
  Wire.begin();
  // Write configuration register
  writeReg(i2c_addr, ICM_20600_CONFIG, 0x00);
  // Write power management register
  writeReg(i2c_addr, ICM_20600_PWR_MGMT_1, 0x01);
  // Check ID
  uint8_t id = readReg(i2c_addr, ICM_20600_WHO_AM_I);
  if (id != ICM_20600_DEVICE_ID) {
    return false;
  }

  return true;
}

bool ICM_20600::init(void) {
  return init(ICM_20600_DEFAULT_ADDR);
}

/* ---Read Functions--- */
void ICM_20600::readTemp() {
  uint8_t tempH = readReg(i2c_addr, ICM_20600_TEMP_OUT_H);
  uint8_t tempL = readReg(i2c_addr, ICM_20600_TEMP_OUT_L);
  uint16_t temp = (tempH << 8) | tempL;
  tmp = (temp/326.8F)+25;
}

void ICM_20600::readAccel() {
  uint8_t xH = readReg(i2c_addr, ICM_20600_ACCEL_XOUT_H);
  uint8_t xL = readReg(i2c_addr, ICM_20600_ACCEL_XOUT_L);
  int x = (xH << 8) | xL;
  uint8_t yH = readReg(i2c_addr, ICM_20600_ACCEL_YOUT_H);
  uint8_t yL = readReg(i2c_addr, ICM_20600_ACCEL_YOUT_L);
  int y = (yH << 8) | yL;
  uint8_t zH = readReg(i2c_addr, ICM_20600_ACCEL_ZOUT_H);
  uint8_t zL = readReg(i2c_addr, ICM_20600_ACCEL_ZOUT_L);
  int z = (zH << 8) | zL;

  float scale = scaleAccel();
  accX = x/scale;
  accY = y/scale;
  accZ = z/scale;
}

void ICM_20600::readGyro() {
  uint8_t xH = readReg(i2c_addr, ICM_20600_GYRO_XOUT_H);
  uint8_t xL = readReg(i2c_addr, ICM_20600_GYRO_XOUT_L);
  int x = (xH << 8) | xL;
  uint8_t yH = readReg(i2c_addr, ICM_20600_GYRO_YOUT_H);
  uint8_t yL = readReg(i2c_addr, ICM_20600_GYRO_YOUT_L);
  int y = (yH << 8) | yL;
  uint8_t zH = readReg(i2c_addr, ICM_20600_GYRO_ZOUT_H);
  uint8_t zL = readReg(i2c_addr, ICM_20600_GYRO_ZOUT_L);
  int z = (zH << 8) | zL;

  float scale = scaleGyro();
  gyrX = x/scale;
  gyrY = y/scale;
  gyrZ = z/scale;
}

void ICM_20600::readVals() {
  readTemp();
  readAccel();
  readGyro();
}

icm_20600_accel_range_t ICM_20600::readAccelRange() {
  uint8_t regVal = readReg(i2c_addr, ICM_20600_ACCEL_CONFIG);
  return (icm_20600_accel_range_t) ((regVal & 0x18) >> 3);
}

icm_20600_gyro_range_t ICM_20600::readGyroRange() {
  uint8_t regVal = readReg(i2c_addr, ICM_20600_GYRO_CONFIG);
  return (icm_20600_gyro_range_t) ((regVal & 0x18) >> 3);
}

/* ---Set Functions--- */
void ICM_20600::setAccelRange(icm_20600_accel_range_t range) {
  uint8_t regVal = (uint8_t) (range << 3);
  writeReg(i2c_addr, ICM_20600_ACCEL_CONFIG, regVal);
}

void ICM_20600::setGyroRange(icm_20600_gyro_range_t range) {
  uint8_t regVal = (readReg(i2c_addr, ICM_20600_GYRO_CONFIG) & 0xE7) | ((uint8_t) (range << 3));
  writeReg(i2c_addr, ICM_20600_GYRO_CONFIG, regVal);
}

/* ---Get Functions--- */
float ICM_20600::temp() {
  return tmp;
}

float ICM_20600::accelX() {
  return accX;
}

float ICM_20600::accelY() {
  return accY;
}

float ICM_20600::accelZ() {
  return accZ;
}

float ICM_20600::gyroX() {
  return gyrX;
}

float ICM_20600::gyroY() {
  return gyrY;
}

float ICM_20600::gyroZ() {
  return gyrZ;
}

/* ---Private Functions--- */
void ICM_20600::writeReg(uint8_t addr, uint8_t reg, uint8_t data) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t ICM_20600::readReg(uint8_t addr, uint8_t reg) {
  uint8_t retVal = 0xFF;
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(addr, (uint8_t) 1);
  if (Wire.available() >= 1) {
   retVal = Wire.read();
  }
  return retVal;
}

float ICM_20600::scaleAccel() {
  icm_20600_accel_range_t range = readAccelRange();
  if (range == ICM_20600_ACCEL_RANGE_2_G)
    return 16384.0F;
  if (range == ICM_20600_ACCEL_RANGE_4_G)
    return 8192.0F;
  if (range == ICM_20600_ACCEL_RANGE_8_G)
    return 4096.0F;
  if (range == ICM_20600_ACCEL_RANGE_16_G)
    return 2048.0F;

   return 1.0;
}

float ICM_20600::scaleGyro() {
  icm_20600_gyro_range_t rangeG = readGyroRange();
  if (rangeG == ICM_20600_GYRO_RANGE_250_DPS)
    return 131.0F;
  if (rangeG == ICM_20600_GYRO_RANGE_500_DPS)
    return 65.5F;
  if (rangeG == ICM_20600_GYRO_RANGE_1000_DPS)
    return 32.8F;
  if (rangeG == ICM_20600_GYRO_RANGE_2000_DPS)
    return 16.4F;

   return 1.0;
}
