#include <wiringPi.h>
#include <zconf.h>
#include <string>
#include <ratio>
#include <iostream>
#include <fstream>

#include "config.h"
#include "afsk_avr.h"
#include "aprs.h"
#include "pin.h"
#include "power.h"

#define ENABLE_PIN 29
#define VCC_PIN 2
#define GND_PIN 9
#define TX_PIN 31

using namespace std;

// term of aprs
static int32_t next_aprs = 1000;

int main(){
    // initial function
    wiringPiSetupGpio();

    // initial pin mode
    pinMode(ENABLE_PIN,OUTPUT);
    pinMopde(TX_PIN,PWM_OUTPUT);

    // set up
    afsk_setup();

    // loop
    while(1){
        string in_line;
        // text2 경로로 !
        ifstream in("/Users/gounchoi/Desktop/IITP_agIoT/MQTT_data_store_module/test2.txt");
        while(getline(in,in_line)){
        }
        in.close();
        string testString = in_line;
        aprs_send(testString);
        next_aprs += APRS_PERIOD * 1000L;
        while (afsk_flush()) {
            power_save();
        }
        sleep(1000);
        power_save();
    }

    return 0;
}
