import threading
from datetime import datetime

end = False

def func(second = 1.0):
        global end
        if end:
            return
        # TODO 받은 데이터 저장한 txt 경로로 !
        f = open("/Users/gounchoi/Desktop/MQTT_data_store_module/test.rtf",'r')
        print(datetime.now().strftime('%Y-%m-%d %H:%M:%S'))
        line = f.readline()
        # TODO 지금 출력만 하는데 어딘가에 저장하려면 해야함 !
        print(line)
        f.close()
        f = open("/Users/gounchoi/Desktop/MQTT_data_store_module/test.rtf", 'w')
        f.close()
        threading.Timer(second, func, [second]).start()

def main():
    func(2.0)

if __name__ == '__main__':
    main()