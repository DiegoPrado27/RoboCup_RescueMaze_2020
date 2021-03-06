/* ROBORREGOS MAZE 2020.
 * Marlon Romo, Emérico Pedraza, Diego Prado, Grecia Flores.
 * This BNO class has all functions to get
 * the robot angle, write on screen, and
 * calibrate all sensors.
 * To get more information, go to BNO.h file.
*/
#include "BNO.h"

BNO::BNO(Multiplexor *multiplexor) {
  I2C_ = multiplexor;
  bno_ = Adafruit_BNO055();
  Serial.println("Orientation Sensor Test");
  Serial.println("");
  I2C_->tcaselect(kBNOID);
  bno_.begin();
  I2C_->tcaselect(kBNOID);
  if (!bno_.begin()) {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  delay(kTimeToPrintBNO);

  bno_.setExtCrystalUse(true);
  sensors_event_t event;
  I2C_->tcaselect(kBNOID);
  bno_.getEvent(&event);

  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");

  delay(kRepose);
}

double BNO::getDifferenceWithZero() {
  double error_generated = 0;
  double current_angle_x = getAngleX();

  if (current_angle_x >= 180) {
    error_generated = (360 - current_angle_x);
  } else {
    error_generated = -(current_angle_x);
  }
  return error_generated;
}

double BNO::getAngleX() {
  sensors_event_t event;
  I2C_->tcaselect(kBNOID);
  bno_.getEvent(&event);

  return event.orientation.x;
}

double BNO::getAngleY() {
  sensors_event_t event;
  I2C_->tcaselect(kBNOID);
  bno_.getEvent(&event);

  return event.orientation.y;
}

double BNO::getAngleZ() {
  sensors_event_t event;
  I2C_->tcaselect(kBNOID);
  bno_.getEvent(&event);

  return event.orientation.z;
}

uint8_t BNO::orientationStatus() {
  uint8_t system, gyro, accel, mag = 0;
  bno_.getCalibration(&system, &gyro, &accel, &mag);

  return mag;
}