from pySerialTransfer import pySerialTransfer as txfer

def main():
    # write pressure to arduino, and read flow rate back
    def write_read(tx_val):

        int_size = link.tx_obj(tx_val, 0)
        send_size = int_size
        link.send(send_size) #send value to Arduino

        while not link.available(): #wait until we get a value from Arduino
            if link.status < 0:
                if link.status == txfer.CRC_ERROR:
                    print('ERROR: CRC_ERROR')
                elif link.status == txfer.PAYLOAD_ERROR:
                    print('ERROR: PAYLOAD_ERROR')
                elif link.status == txfer.STOP_BYTE_ERROR:
                    print('ERROR: STOP_BYTE_ERROR')
                else:
                    print('ERROR: {}'.format(link.status))

        flow = link.rx_obj(obj_type=float,
                                 obj_byte_size=4) #read response from Arduino
        return flow

    link = txfer.SerialTransfer('COM5')  #Change this to the right COM port
    link.open()
    time.sleep(2) # allow some time for the Arduino to completely reset
    print('Connected to device')

    tx_val, rx_val = 0, 0

    while True:
        rx_val = write_read(tx_val)
        print('sent: {}  received: {}'.format(tx_val, rx_val))
        tx_val += 1

if __name__ == '__main__':
    main()
