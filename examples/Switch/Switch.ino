/**
  @file Switch.ino
  Modbus-Arduino Example - Switch (Modbus IP ESP8266 AT)
  Copyright by André Sarmento Barbosa
  https://github.com/epsilonrt/modbus-esp8266at
*/

#include <ESP8266.h>
#include <Modbus.h>
#include <ModbusEsp8266AT.h>

ESP8266 wifi(Serial, 9600);

//Modbus Registers Offsets (0-9999)
const int SWITCH_ISTS = 100;
//Used Pins
const int switchPin = 5;

//ModbusEsp8266AT object
ModbusEsp8266AT mb;

void setup() {
    //Config Modbus IP
    mb.config(wifi, "your_ssid", "your_password");
    //Set ledPin mode
    pinMode(switchPin, INPUT);
    // Add SWITCH_ISTS register - Use addIsts() for digital inputs
    mb.addIsts(SWITCH_ISTS);
}

void loop() {
   //Call once inside loop() - all magic here
   mb.task();

   //Attach switchPin to SWITCH_ISTS register
   mb.Ists(SWITCH_ISTS, digitalRead(switchPin));
}
