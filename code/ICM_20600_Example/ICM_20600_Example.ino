#include "ICM_20600.h"

ICM_20600 icm;

#define debugMode false

void setup() {
  Serial.begin(9600);
  
  if (debugMode) Serial.println("Initialising ICM 20600...");
  if (icm.init()) {
    if (debugMode) Serial.println("Success");
  } else {
    if (debugMode) Serial.println("Failure");
    while(1) {
      delay(100);
    }
  }

  /* Edit/Print Accelerometer Range */
  //icm.setAccelRange(ICM_20600_ACCEL_RANGE_8_G);

  if (debugMode) {
    icm_20600_accel_range_t range = icm.readAccelRange();
    if (range == ICM_20600_ACCEL_RANGE_2_G)
      Serial.println("2G");
    if (range == ICM_20600_ACCEL_RANGE_4_G)
      Serial.println("4G");
    if (range == ICM_20600_ACCEL_RANGE_8_G)
      Serial.println("8G");
    if (range == ICM_20600_ACCEL_RANGE_16_G)
      Serial.println("16G");
  }

  /* Edit/Print Gyroscope Range */
  //icm.setGyroRange(ICM_20600_GYRO_RANGE_1000_DPS);

  if (debugMode) {
    icm_20600_gyro_range_t rangeG = icm.readGyroRange();
    if (rangeG == ICM_20600_GYRO_RANGE_250_DPS)
      Serial.println("250DPS");
    if (rangeG == ICM_20600_GYRO_RANGE_500_DPS)
      Serial.println("500DPS");
    if (rangeG == ICM_20600_GYRO_RANGE_1000_DPS)
      Serial.println("1000DPS");
    if (rangeG == ICM_20600_GYRO_RANGE_2000_DPS)
      Serial.println("2000DPS");
  }
}

void loop() {
  // Get latest readings from ICM 20600
  icm.readVals();

  if (debugMode) {
    /* Slow print mode with formatting */
    // Print accelerometer readings
    Serial.println("");
    Serial.print("Accelerometer: ");
    Serial.print("x: ");
    Serial.print(icm.accelX());
    Serial.print(", y: ");
    Serial.print(icm.accelY());
    Serial.print(", z: ");
    Serial.print(icm.accelZ());
    Serial.println("   G");
  
    // Print gyroscope readings
    Serial.print("Gyroscope:     ");
    Serial.print("x: ");
    Serial.print(icm.gyroX());
    Serial.print(", y: ");
    Serial.print(icm.gyroY());
    Serial.print(", z: ");
    Serial.print(icm.gyroZ());
    Serial.println("   DPS");
    delay(500);
  } else {
    /* Fast print mode with comma-seperation only */
    Serial.print(icm.accelX());
    Serial.print(",");
    Serial.print(icm.accelY());
    Serial.print(",");
    Serial.print(icm.accelZ());
    Serial.print(",");
    Serial.print(icm.gyroX());
    Serial.print(",");
    Serial.print(icm.gyroY());
    Serial.print(",");
    Serial.println(icm.gyroZ());
    delay(50);
  }
}
