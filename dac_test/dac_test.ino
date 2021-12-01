#include "SerialTransfer.h"
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting");
  dac.begin(0x60);
}

int output_code = 0; // 12 bit DAC code to control pressure sensor

void loop() // there is no delay in this loop, so we can see the max waveform frequency (very slow)
{
   dac.setVoltage(output_code, false);
   output_code = (output_code == 1023) ? 0 : output_code + 1; // sawtooth wave
}
