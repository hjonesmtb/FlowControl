import uProcess
import PySimpleGUI as sg
import time


""" This code demonstrates the basic control of an AV801 valve, using the EIB200 and 4VM02. 
	There is a basic GUI for selecting the device adresses, and the valve settings. 
	This code assumes the EIB200 is connected to the 4VM02 with the 20 pin cable,
	and that channel 1 of the 4VM02 is connected to the AV801 with the 6 pin ribbon cable.

	The basic code for controlling the valve is like this:
	
	eib = uProcess.CEIB() # create EIB python object
	time.sleep(2) 

	eib.InitConnection(COM_PORT) # open a USB connection to the EIB200, on COM_PORT

	fourVM = eib.New4VM(DEVICE_ADDRESS) #connect to the 4VM02

	fourVM.CmdSelect (CHAN, STATE) # Move channel CHAN (1-4) into position STATE (1-8)
"""

#boiler plate code for start page. Choose COM ports
def com_windows():
    layout = [
			     [sg.Text('Valve Control', size=(40, 1),
					justification='center', font='Helvetica 20')],
       			 [sg.Text('EIB200 COM port', size=(15, 1), font='Helvetica 12'), sg.InputText('6')],
       			 [sg.Text('4VM Adress', size=(15, 1), font='Helvetica 12'), sg.InputText('10')],

		         [sg.Canvas(key='controls_cv')],
                 [sg.Canvas(size=(650, 30), key='-CANVAS-')],

		        [sg.Button('Submit', size=(10, 1), pad=((280, 0), 3), font='Helvetica 14')]
		        ]

    # create the form and show it without the plot
    window = sg.Window('Start Screen',
                layout, finalize=True)

    canvas_elem = window['-CANVAS-']
    canvas = canvas_elem.TKCanvas
    
    return window

#boiler plate code for GUI and animation
def control_windows():
    layout = [
			     [sg.Text('Valve Control', size=(40, 1),
					justification='center', font='Helvetica 20')],
		         [sg.Button('Channel 1', size=(8,1), button_color=('white', 'green'), key='1'),
		         sg.Button('Channel 2', size=(8,1), button_color=('white', 'green'), key='2'),
		         sg.Button('Channel 3', size=(8,1), button_color=('white', 'green'), key='3'),
		         sg.Button('Channel 4', size=(8,1), button_color=('white', 'green'), key='4'),
		         sg.Button('Channel 5', size=(8,1), button_color=('white', 'green'), key='5'),
		         sg.Button('Channel 6', size=(8,1), button_color=('white', 'green'), key='6'),
		         sg.Button('Channel 7', size=(8,1), button_color=('white', 'green'), key='7'),
		         sg.Button('Channel 8', size=(8,1), button_color=('white', 'green'), key='8')],

		         [sg.Canvas(key='controls_cv')],
                 [sg.Canvas(size=(650, 30), key='-CANVAS-')],

		        [sg.Button('Exit', size=(10, 1), pad=((280, 0), 3), font='Helvetica 14')]
		        ]

    # create the form and show it without the plot
    window = sg.Window('Start Screen',
                layout, finalize=True)

    canvas_elem = window['-CANVAS-']
    canvas = canvas_elem.TKCanvas
    
    return window

def main():

	COM_select = com_windows()
	while True:
		event, values = COM_select.read(timeout=10)

		if event in ('Submit', None):
			eib_com = int(values[0])
			fourVM_addr = int(values[1])

			eib.InitConnection(eib_com) # COM port we just chose

			if eib.New4VM(fourVM_addr) is None:
				print('Invalid COM or Address')
				continue
			else:
				break

	a = eib.New4VM(fourVM_addr)

	COM_select.close()

	window = control_windows()
	channels = ('1','2','3','4','5','6','7','8')
	while True:
		event, values = window.read(timeout=10)

		if event in channels:

			a.CmdSelect (1, int(event)) # Move channel 1 into position
			time.sleep(2.5)             # wait until valve is in position (2.5s max actuation time)

			for e in channels:
				if e == event:
					window.Element(e).Update(button_color=(('white', 'green')))
				else:
					window.Element(e).Update(button_color=(('white', 'red')))

		elif event in ('Exit', None):
			break

	window.close()

if __name__ == '__main__':
	eib = uProcess.CEIB() 
	time.sleep(2) # allow some time for the Arduino to completely reset

	main()

