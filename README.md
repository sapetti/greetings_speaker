# GREETINGS_SPEAKER

Project to play a ramdon sound when some moves close to a PIR sensor.

## Hardware

* Raspberry PI
* Esp32
* PIR sensor HC-SR501
* Speakers

PIR ---> Esp32 )))Wifi))) Raspberry ---> Speakers

## Software

* NodeJS for a REST API
* OmxPlayer to play sound on Raspbian
* Arduino IDE + [Esp32 Board setup](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
* [Esp Driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

## Other

* Power save with Deep Sleep in Esp32
* Youtube-DL to download sound files: ./trim_video.sh "https://www.youtube.com/watch?v=......"
