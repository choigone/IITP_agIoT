#include <wiringPi.h>
#include <printf.h>

#define PIN 29

int main() {
    //set up

    // initial function
    wiringPiSetupGpio();

    // initial pin mode
    pinMode(PIN,OUTPUT);

    // loop


    while(1){
        printf("HIGH");
        digitalWrite(PIN,HIGH);
        delay(1000); //sleep
        printf("LOW");
        digitalWrite(PIN,LOW);
        delay(1000); //sleep
    }

    return 0;
}