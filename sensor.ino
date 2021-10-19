#include "SerialTransfer.h"
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;
SerialTransfer pc;

void setup()
{

  Serial.begin(115200);

  Serial.println("Starting");

  dac.begin(0x60);
  pc.begin(Serial);
}

int pressureCode = 0; // 12 bit DAC code to control pressure sensor
float flow = 0.1;

void loop()
{
  if(pc.available())
  {
    pc.rxObj(pressureCode); // read pressure command from pc

     //dac.setVoltage(pressureCode, false);
    
    //flow = flow_meter.read(flow)
    
    if ( flow < 1.01 && flow > 0.99)
      flow = 0.1;
    else
      flow += 0.1;
    
    pc.sendDatum(flow); // send updated flow rate to pc
  }
}
