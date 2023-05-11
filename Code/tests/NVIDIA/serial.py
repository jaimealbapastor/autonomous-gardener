import glob
import sys
import serial


def findPort():
    """Find the serial port that the Arduino is connected to.
    """
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')
    
    result = []
    
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result

def sendToSerial(message, port = 'COM3'):
    """Send the data to the serial port.
    """
    # Open the serial port
    ser = serial.Serial(port, 9600)
    # Write the data to the serial port
    ser.write(message)  
    # Close the serial port
    ser.close()
