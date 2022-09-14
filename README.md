
# OpenDragy
A DIY drag time performance tracker.

Designed to pair with a high resolution GPS, OpenDragy (originally DIYDragy) will let you measure the acceleration and speed performance characteristics of your vehicle with similar results to what you get at a drag strip.

## Hardware Requirements
You can either use an [ESP32](https://github.com/ConnorHowell/OpenDragy/tree/master/Hardware#using-an-esp32) **or a** dedicated [nRF52 bluetooth module](https://github.com/ConnorHowell/OpenDragy/tree/master/Hardware#using-an-nr52-module). Both require the Neo-M8N GPS module.

## Software Requirements

- [u-center by u-blox](https://www.u-blox.com/en/product/u-center) (For programming the GPS module)
 - Arduino IDE (If using an ESP32)
 - Requirements for using an nRF52 can be found [here](https://github.com/ConnorHowell/OpenDragy/tree/master/nRF52#bleuart-bridge)

## Programming the GPS module
Programming the GPS module can be done by loosely following [this video](https://youtu.be/TwhCX0c8Xe0?t=494) @ 08:14 onwards. 
In essence you need to connect the serial output of the GPS module directly to a windows PC (you can do this using an FTDI cable or you can use this [arduino sketch](https://github.com/ConnorHowell/OpenDragy/tree/master/ESP32#serialtoserial)) Make sure you have the necessary drivers and select the correct COM port and baud rate (9600 if using FTDI, 115200 for the ESP32 bridge method). Follow the video to: disable NMEA messages, set the polling rate to 10hz and enable the UBX messages. **Important, the video shows "POSLLH" being enabled; we also need to enable the "SAT" message.** Once those changes have been made be sure to save the config (the video shows 2 seperate ways to do this).

## Images
|Main Screen| Results List | Run Result | Shared Result |
|--|--|--|--|
| ![Main Screen](https://github.com/ConnorHowell/OpenDragy/blob/master/Media/Main%20Screen.png?raw=true) | ![Results List](https://github.com/ConnorHowell/OpenDragy/blob/master/Media/Results%20List.png?raw=true) | ![Run Result](https://github.com/ConnorHowell/OpenDragy/blob/master/Media/Result.png?raw=true) | ![Shared Result](https://github.com/ConnorHowell/OpenDragy/blob/master/Media/ShareResults.png?raw=true) |
## TODO

 - [ ] Create GitHub action to build iOS app
 - [ ] Add instructions for installing iOS app (AltStore?)
 - [ ] Document GPS programming instead of relying on a video!
 - [ ] Add video recording feature (0-60 time overlay)
 - [ ] Get app on App Store **[MAYBE]**
 - [ ] Create Android version of the App **[MAYBE]**
 
## Credits

 - [pyjamasam](https://github.com/pyjamasam/DIYDragy) for creating the original 'DIYDragy' project
