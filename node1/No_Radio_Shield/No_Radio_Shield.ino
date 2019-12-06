/* trackuino copyright (C) 2010  EA5HAV Javi
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

// Trackuino custom libs
#include "config.h"
#include "afsk_avr.h"
#include "aprs.h"
#include "pin.h"
#include "power.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "dht.h"

// Module variables
static int32_t next_aprs = 1000;

dht DHT;
#define dht_apin A0 // Analog Pin sensor is connected to
#define vh400_apin A1 // Analog pin for VH400

// you can change the pin numbers to match your wiring:
SoftwareSerial mySerial(3, 2);

int highval = 9;
int count = 0;

void setup()
{
  afsk_setup();

  delay(1000);
  Serial.begin(4800); delay(1000);
  Serial.println("C"); delay(3);
  Serial.print("MW1AW\r\n"); delay(10);              //SET YOUR CALLSIGN HERE, HERE YOU SEE W1AW                       
  Serial.print("PWIDE1-1,WIDE2-1\r\n"); delay(10);   //SET DIGIPATH HERE
  pinMode(highval, OUTPUT); delay(1000);
  Serial.begin(115200); delay(3000);
}

void loop()
{     
  // Time for another APRS frame
  if ((int32_t) (millis() - next_aprs) >= 0) {
    DHT.read11(dht_apin);
  
    String data = "";
    count++;
  
    data = data + "##";
    data = data + (String)DHT.temperature;
    data = data + "!" + (String)DHT.humidity;
    data = data + "!"+(String)analogRead(vh400_apin);
    Serial.println("test : " + (String)count);
    Serial.println("temperature : " + (String)DHT.temperature);
    Serial.println("humidity : " + (String)DHT.humidity);
    Serial.println("test : " + (String)analogRead(vh400_apin));
    
    aprs_send(data);
    next_aprs += APRS_PERIOD * 1000L;
    while (afsk_flush()) {
      power_save();
    }

  } else {
    // Discard GPS data received during sleep window
    while (Serial.available()) {
      Serial.read();
    }
  }
  
  power_save(); // Incoming GPS data or interrupts will wake us up
}
