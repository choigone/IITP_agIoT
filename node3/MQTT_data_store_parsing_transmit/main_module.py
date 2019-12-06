import threading
from datetime import datetime
import serial

end = False

def func(second = 1.0):
        global end
        if end:
            return
        f = open("/Users/gounchoi/Desktop/IITP_agIoT/node3/MQTT_data_store_module/test.txt",'r')
        print(datetime.now().strftime('%Y-%m-%d %H:%M:%S'))
        s = f.read()
        print(s)
        f.close()
        f = open("/Users/gounchoi/Desktop/IITP_agIoT/node3/MQTT_data_store_module/test.txt", 'w')
        f.close()

        lines = s.splitlines()
        try:
                datas = lines[-1].split("!")
        except:
                print("exceptions")

        ser = serial.Serial('/dev/ttyUSB1',9600)
        if datas[-1] < 200 :
                ser.write('1')
        else :
                ser.write('0')

        threading.Timer(second, func, [second]).start()

def main():
    func(2.0)

if __name__ == '__main__':
    main()