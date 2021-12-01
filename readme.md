Files for flow control system. 

py_controller.py is a GUI (made with PySimpleGUI) that connects to an arduino, and remotely controls the flow rate. It also has an interface to select the flow channel to deliver reagent to. 

ino_controller.ino is an arduino program to read from a flow meter, and write to a DAC/pressure controller.

Labsmith_uProcess_Python_support is a reference document for the valve controller commands.

The valve controller is connected directly to the PC.

dac_test.ino, flow_sensor_test.ino, ino_TxRx.ino and py_TxRx.py are example scripts that show the basic interfacing code for each component.


Original flow sensor example code: https://github.com/Sensirion/arduino-liquid-flow-snippets/blob/master/SF04/example_01_simple_measurement/example_01_simple_measurement.ino

Original DAC example code: https://media.digikey.com/pdf/Data%20Sheets/Sparkfun%20PDFs/MCP4725_HookupGuide.pdf

Original Serial Transfer code: https://github.com/PowerBroker2/pySerialTransfer
