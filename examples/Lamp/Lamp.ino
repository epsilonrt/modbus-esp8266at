/**
  @file Lamp.ino
  Modbus-Arduino Example - Lamp (Modbus IP ESP8266 AT)
  Copyright by André Sarmento Barbosa
  https://github.com/epsilonrt/modbus-esp8266at
*/

#include <ESP8266.h>
#include <Modbus.h>
#include <ModbusEsp8266AT.h>

ESP8266 wifi(Serial, 9600);

//Modbus Registers Offsets (0-9999)
const int LAMP1_COIL = 100;
//Used Pins
const int ledPin = 13;

//ModbusEsp8266AT object
ModbusEsp8266AT mb;

void setup() {
    //Config Modbus IP
    mb.config(wifi, "your_ssid", "your_password");
    //Set ledPin mode
    pinMode(ledPin, OUTPUT);
    // Add LAMP1_COIL register - Use addCoil() for digital outputs
    mb.addCoil(LAMP1_COIL);
}

void loop() {
   //Call once inside loop() - all magic here
   mb.task();

   //Attach ledPin to LAMP1_COIL register
   digitalWrite(ledPin, mb.Coil(LAMP1_COIL));
}
