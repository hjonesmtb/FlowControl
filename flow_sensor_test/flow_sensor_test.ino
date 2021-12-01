#include <Wire.h> // Arduino library for I2C

const int ADDRESS = 0x40; // Standard address for Liquid Flow Sensors

// -----------------------------------------------------------------------------
// Arduino setup routine, just runs once:
// -----------------------------------------------------------------------------
void setup() {


  // Add documentation here for pinout (wire colours)
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT); 
  digitalWrite(A2,HIGH);
  digitalWrite(A3,LOW);
  
  int ret;

  Serial.begin(9600); // initialize serial communication
  Wire.begin();       // join i2c bus (address optional for master)
  Serial.println("Starting");

  do {
    // Soft reset the sensor
    Wire.beginTransmission(ADDRESS);
    Wire.write(0xFE);
    
    ret = Wire.endTransmission();
    Serial.println("resetting");
    if (ret != 0) {
      Serial.println("Error while sending soft reset command, retrying...");
    }
    
  } while (ret != 0);

  delay(50); // wait long enough for chip reset to complete

  Serial.println("Setup");
}

// -----------------------------------------------------------------------------
// The Arduino loop routine runs over and over again forever:
// -----------------------------------------------------------------------------
void loop() {

  Serial.println("Looping");
  
  int ret;
  uint16_t raw_sensor_value;
  int16_t signed_sensor_value;

  // To perform a measurement, first send 0xF1 to switch to measurement mode,
  // then read 2 bytes + 1 CRC byte from the sensor.
  Wire.beginTransmission(ADDRESS);
  Wire.write(0xF1);
  ret = Wire.endTransmission();
  if (ret != 0) {
    Serial.println("Error during write measurement mode command");

  } else {
    Wire.requestFrom(ADDRESS, 2);       // reading 2 bytes ignores the CRC byte
    if (Wire.available() < 2) {
      Serial.println("Error while reading flow measurement");

    } else {
      raw_sensor_value  = Wire.read() << 8; // read the MSB from the sensor
      raw_sensor_value |= Wire.read();      // read the LSB from the sensor

      Serial.print("raw value from sensor: ");
      Serial.print(raw_sensor_value);

      signed_sensor_value = (int16_t) raw_sensor_value;
      Serial.print(", signed value: ");
      Serial.println(signed_sensor_value);
    }
  }

  delay(1000); // milliseconds delay between reads (for demo purposes)
}
