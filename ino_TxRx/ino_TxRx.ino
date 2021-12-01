#include "SerialTransfer.h"
SerialTransfer pc;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting");
  pc.begin(Serial);
}

float tx_val = 0;
float rx_val = 0;

void loop()
{
  if(pc.available()) // wait until we get a reading from PC
  {
    pc.rxObj(rx_val); // read from pc into rx_val
    tx_val = rx_val;  // echo back to PC.   
    pc.sendDatum(tx_val); // send response to PC
  }
}
