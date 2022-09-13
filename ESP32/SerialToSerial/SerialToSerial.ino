//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "HardwareSerial.h"

HardwareSerial UART(2);

void setup() {
  Serial.begin(115200);
  UART.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  if (Serial.available()) {
    UART.write(Serial.read());
  }
  if (UART.available()) {
    Serial.write(UART.read());
  }
}
