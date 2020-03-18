#ifndef _ICM_20600_H
#define _ICM_20600_H

/* ---Defines--- */
// I2C Address
#define ICM_20600_DEFAULT_ADDR 0x69
// Device ID
#define ICM_20600_DEVICE_ID 0x11

// Registers
// Config
#define ICM_20600_CONFIG 0x1A
#define ICM_20600_GYRO_CONFIG 0x1B
#define ICM_20600_ACCEL_CONFIG 0x1C
#define ICM_20600_ACCEL_CONFIG2 0x1D
// Accel Out
#define ICM_20600_ACCEL_XOUT_H 0x3B
#define ICM_20600_ACCEL_XOUT_L 0x3C
#define ICM_20600_ACCEL_YOUT_H 0x3D
#define ICM_20600_ACCEL_YOUT_L 0x3E
#define ICM_20600_ACCEL_ZOUT_H 0x3F
#define ICM_20600_ACCEL_ZOUT_L 0x40
// Temp Out
#define ICM_20600_TEMP_OUT_H 0x41
#define ICM_20600_TEMP_OUT_L 0x42
// Gyro Out
#define ICM_20600_GYRO_XOUT_H 0x43
#define ICM_20600_GYRO_XOUT_L 0x44
#define ICM_20600_GYRO_YOUT_H 0x45
#define ICM_20600_GYRO_YOUT_L 0x46
#define ICM_20600_GYRO_ZOUT_H 0x47
#define ICM_20600_GYRO_ZOUT_L 0x48
// Power Management
#define ICM_20600_PWR_MGMT_1 0x6B
#define ICM_20600_PWR_MGMT_2 0x6C
// ID
#define ICM_20600_WHO_AM_I 0x75

/* ---Typedefs--- */
typedef enum {
  ICM_20600_ACCEL_RANGE_2_G,
  ICM_20600_ACCEL_RANGE_4_G,
  ICM_20600_ACCEL_RANGE_8_G,
  ICM_20600_ACCEL_RANGE_16_G
} icm_20600_accel_range_t;

typedef enum {
  ICM_20600_GYRO_RANGE_250_DPS,
  ICM_20600_GYRO_RANGE_500_DPS,
  ICM_20600_GYRO_RANGE_1000_DPS,
  ICM_20600_GYRO_RANGE_2000_DPS
} icm_20600_gyro_range_t;

/* ---Class Definition--- */
class ICM_20600 {
  public:
    /* ---Functions--- */
    // Constructor
    ICM_20600();
    // Initialisation function
    bool init();
    bool init(uint8_t addr);

    /* Read Functions */
    // Read temperature value from ICM 
    void readTemp();
    // Read accelerometer values from ICM 
    void readAccel();
    // Read gyroscope values from ICM 
    void readGyro();
    // Read all values from ICM 
    void readVals();
    // Read current accelerometer range
    icm_20600_accel_range_t readAccelRange();
    // Read current gyroscope range
    icm_20600_gyro_range_t readGyroRange();

    /* Set Functions */
    // Set the accelerometer range
    void setAccelRange(icm_20600_accel_range_t range);
    // Set the gyroscope range
    void setGyroRange(icm_20600_gyro_range_t range);
    
    /* Get Functions */
    // Return last read temperature value
    float temp();
    // Return last read accelerometer x value
    float accelX();
    // Return last read accelerometer y value
    float accelY();
    // Return last read accelerometer z value
    float accelZ();
    // Return last read gyro x value
    float gyroX();
    // Return last read gyro y value
    float gyroY();
    // Return last read gyro z value
    float gyroZ();

  private:
    /* ---Variables--- */
    float tmp, accX, accY, accZ, gyrX, gyrY, gyrZ;
    uint8_t i2c_addr;
    /* ---Functions--- */
    // Write to ICM register
    void writeReg(uint8_t addr, uint8_t reg, uint8_t data);
    // Read from ICM register
    uint8_t readReg(uint8_t addr, uint8_t reg);
    // Return scale value for accelerometer readings
    float scaleAccel();
    // Return scale value for gyro readings
    float scaleGyro();
};

#endif
