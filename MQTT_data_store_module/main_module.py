import threading
from datetime import datetime

end = False

def func(second = 1.0):
        global end
        if end:
            return
        f = open("/Users/gounchoi/Desktop/IITP_agIoT/MQTT_data_store_module/test.txt",'r')
        print(datetime.now().strftime('%Y-%m-%d %H:%M:%S'))
        line = f.read()
        print(line)
        f.close()
        f = open("/Users/gounchoi/Desktop/IITP_agIoT/MQTT_data_store_module/test.txt", 'w')
        f.close()
        f = open("/Users/gounchoi/Desktop/IITP_agIoT/MQTT_data_store_module/test2.txt", 'w')
        f.write(line)
        f.close()
        threading.Timer(second, func, [second]).start()

def main():
    func(2.0)

if __name__ == '__main__':
    main()