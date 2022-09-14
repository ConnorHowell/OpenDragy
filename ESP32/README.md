# Prerequisites

 - Arduino IDE
 - ESP32 Module for Arduino IDE. [Installation instructions](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#installing-using-arduino-ide)
 - USB to UART bridge driver for ESP32 (Commonly: [CP210x USB to UART Bridge](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers))

## SerialToSerial
This arduino sketch is used to bridge the ESP32 built in serial to the GPS UART useful for programming the GPS module in the event you don't have access to a FTDI cable. If you use this script for u-center, you must change the baud rate in u-center to 115200 (the default is 9600 for the GPS module).
## ble_uart_bridge
This is the actual firmware for when the device is ready to go; this simple arduino sketch bridges the GPS module UART connection to a BLE service for the app to receive information in real time. You can find the pin assignments for this here: [Wiring up the ESP32](https://github.com/ConnorHowell/OpenDragy/tree/master/Hardware#wiring-up-the-esp32)
