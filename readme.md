Files for flow control system. 

read_flow.py is a GUI (made with PySimpleGUI) that connects to an arduino, and remotely controls the flow rate. It also has an interface to select the flow channel to deliver reagent to. 

sensor.ino is an arduino program to read from a flow meter, and write to a DAC/pressure controller.

The valve controller is connected directly to the PC.
