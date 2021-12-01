#include "SerialTransfer.h"
#include <Wire.h>

const int ADDRESS = 0x40; // Standard address for Liquid Flow Sensors

SerialTransfer pc;

void setup()
{
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT); 
  digitalWrite(A2,HIGH);
  digitalWrite(A3,LOW);
  
  int ret;
    
  Serial.begin(115200);

  Wire.begin();       // join i2c bus

  do {
    delay(1000); // Error handling for example: wait a second, then try again

    // Soft reset the sensor
    Wire.beginTransmission(ADDRESS);
    Wire.write(0xFE);
    ret = Wire.endTransmission();
    if (ret != 0) {
      Serial.println("Error while sending soft reset command, retrying...");
      continue;
    }
    delay(50); // wait long enough for reset

    // Switch to measurement mode
    Wire.beginTransmission(ADDRESS);
    Wire.write(0xF1);
    ret = Wire.endTransmission();
    if (ret != 0) {
      Serial.println("Error during write measurement mode command");
    }
  } while (ret != 0);
  Serial.println("Starting");
  
  pc.begin(Serial);
}

int pressureCode = 0; // 12 bit DAC code to control pressure sensor

void loop()
{
  if(pc.available())
  {
    pc.rxObj(pressureCode); // read pressure command from pc

     //dac.setVoltage(pressureCode, false);

    int ret;
    uint16_t raw_sensor_value;
    float sensor_reading;
  
    Wire.requestFrom(ADDRESS, 2); // reading 2 bytes ignores the CRC byte
    if (Wire.available() < 2) {
      Serial.println("Error while reading flow measurement");
    } else {
      raw_sensor_value  = Wire.read() << 8; // read the MSB from the sensor
      raw_sensor_value |= Wire.read();      // read the LSB from the sensor
      sensor_reading = (float) ((int16_t) raw_sensor_value) / 270;  
    }
    
    pc.sendDatum(sensor_reading); // send updated flow rate to pc
  }
}
