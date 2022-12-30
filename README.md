Modbus Library for Arduino - Over TCP/IP implementation for ESP8266 AT controller
=================================================================================

This library allows your Arduino to communicate via Modbus protocol. The Modbus is a master-slave protocol
used in industrial automation and can be used in other areas, such as home automation.

The Modbus generally uses serial RS-232 or RS-485 as physical layer (then called Modbus Serial) and
TCP/IP via Ethernet or WiFi (Modbus TCP).

In the current version the library allows the Arduino operate **as a slave**, supporting Modbus over TCP.

## How to

There are four classes corresponding to five headers that may be used:

* [Modbus](http://github.com/epsilonrt/modbus-arduino ) - Base Library
* [ModbusSerial](https://github.com/epsilonrt/modbus-serial) - Modbus Serial RTU Library    
* [ModbusEthernet](https://github.com/epsilonrt/modbus-ethernet) - Modbus TCP Library (standard Ethernet Shield)   
* [ModbusEthercard](https://github.com/epsilonrt/modbus-ethercard) - Modbus TCP Library (for ENC28J60 chip)  
* [ModbusEsp8266AT](https://github.com/epsilonrt/modbus-esp8266at) - Modbus IP Library (for ESP8266 chip with AT firmware)   

By opting for Modbus Serial or Modbus TCP you must include in your sketch the corresponding header and the base library header, eg:

    #include <Modbus.h>
    #include <ModbusSerial.h>

## ModbusEsp8266AT

Modules based on ESP8266 are quite successful and cheap. With firmware that
responds to AT commands (standard on many modules) you can use them as a
simple wireless network interface to the Arduino.

The firmware used in the module (at_v0.20_on_SDKv0.9.3) is available at:
http://www.electrodragon.com/w/ESP8266_AT-command_firmware

(Other AT firmwares compatible with ITEAD WeeESP8266 Library should work)

Warning: Firmware such as NodeMCU and MicroPython does not work because libraries
used here depend on a firmware that responds to AT commands via serial interface.
The firmware mentioned are used when you want to use ESP8266 modules without the Arduino.

You will need the WeeESP8266 library (ITEAD) for the Arduino. Download from:

https://github.com/itead/ITEADLIB_Arduino_WeeESP8266 and install in your IDE.

**Notes:**

1. The ESP8266 library can be used with a serial interface by hardware (HardwareSerial) or
by software (SoftwareSerial). By default it will use HardwareSerial, to change edit the file
ESP8266.h removing the comments from line:


		#define ESP8266_USE_SOFTWARE_SERIAL


2. Remember that the power of ESP8266 module is 3.3V.

For Modbus IP (ESP8266 AT) there is four examples that can be accessed from the Arduino interface.
Let's look at the example Lamp.ino (only the parts concerning Modbus will be commented):

    #include <ESP8266.h>
    #include <SoftwareSerial.h>   // Only if using Softwareserial to communicate with the module
    #include <Modbus.h>
    #include <ModbusEsp8266AT.h>

Inclusion of the necessary libraries.

    SoftwareSerial wifiSerial(2 , 3);

Creates the serial interface via software using pins 2 (RX) and 3 (TX). So it can use
hardware for the serial communication with the PC (e.g. for debugging purposes) in Arduino models that have only one serial (Ex .: Arduino UNO).

    ESP8266 wifi(wifiSerial, 9600); // You will need to eanble the constructor for SoftwareSerial in the WeeESP8266 library (ITEAD)

Create the wifi object (ESP8266) specifying the rate in bps.
Warning: If you use SoftwareSerial do not specify a baud rate of 115200bps or more for the serial because it will not function. Some firmware / modules comes with 115200bps by default. You will have to change the module via AT command:

    AT+CIOBAUD=9600

Continuing with our example:

    const int LAMP1_COIL = 100;

Sets the Modbus register to represent a lamp or LED. This value is the offset (0-based) to be placed in its supervisory or testing software.
Note that if your software uses offsets 1-based the set value there should be 101, for this example.

    ModbusIP mb;

Create the mb instance (ModbusSerial) to be used.

    mb.config(wifi, "your_ssid", "your_password");

Configure ESP8266 module. The values quoted correspond to the network name (SSID) and security key.
By default IP configuration is received via DHCP. See the end of the section how to have an Static IP
(important so you do not need to change the master / supervisor if the IP changes).

Folowing, we have:

    mb.addCoil (LAMP1_COIL);

Adds the register type Coil (digital output) that will be responsible for activating the LED or lamp and verify their status.
The library allows you to set an initial value for the register:

    mb.addCoil (LAMP1_COIL, true);

In this case the register is added and set to true. If you use the first form the default value is false.

    mb.task();

This method makes all magic, answering requests and changing the registers if necessary, it should be called only once, early in the loop.

    digitalWrite(ledPin, mb.Coil(LAMP1_COIL));

Finally the value of LAMP1_COIL register is used to drive the lamp or LED.

Quite similarly to other examples show the use of other methods available in the library.


**Using a static IP on the ESP8266 module**

We are aware today of two options:

1. In your router configure the MAC address of the module so that the IP address provided by
DHCP is always the same (Most routers have this feature).

2. In your code, include two lines to change the IP address after the module configuration:

    mb.config(wifi, "your_ssid", "your_password");
    delay(1000);
    wifiSerial.println("AT+CIPSTA=\"192.168.1.44\"");


Note: For the module to  receive IP via DHCP again you will need to remove the lines
and run (at least once) the command: AT + CWDHCP = 1.1 via direct connection to the module, either:


    wifiSerial.println("AT+CWDHCP=1,1");

Contributions
=============
http://github.com/epsilonrt/modbus-arduino  
epsilonrt (at) gmail (dot) com  
prof (at) andresarmento (dot) com  

License
=======
The code in this repo is licensed under the BSD New License. See LICENSE for more info.

