Files for flow control system. 

read_flow.py is a GUI (made with PySimpleGUI) that connects to an arduino, and remotely controls the flow rate. It also has an interface to select the flow channel to deliver reagent to. 

sensor.ino is an arduino program to read from a flow meter, and write to a DAC/pressure controller.

Labsmith_uProcess_Python_support is a reference document for the valve controller commands.

The valve controller is connected directly to the PC.

Reference code:

Reading from flow sensor: https://github.com/Sensirion/arduino-liquid-flow-snippets/blob/master/SF04/example_01_simple_measurement/example_01_simple_measurement.ino
Writing to DAC: https://media.digikey.com/pdf/Data%20Sheets/Sparkfun%20PDFs/MCP4725_HookupGuide.pdf

