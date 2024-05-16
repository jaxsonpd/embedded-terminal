# Embedded Terminal

This is a terminal designed to run on the avr series of micro controller which offers some basic functions.

# Documentation
## Commands

`help`: View the available commands and get general information about the system.

`clear`: Clear the terminal screen using the VT100 escape sequence.

`led`: Toggle an lead connected to a spesific pin (in this case pin 13 on the arduino uno)
 
# Setup

A full installation and setup process can be found in SETUP.md

But assuming the target device is ATMEL Mega328P (Arduino Uno) then the device can be programmed using:

```
make flash serial
```

## Monitoring the Serial Port
### Serial monitor settings

| Setting | Value |
| ------ | --------- |
| EOL sent | `\n` |
| EOL reciving | `\r\n` |
| Baud Rate | `56700` |
| Encoding | `8n1` |

### Installation
To interact with the terminal use a serial monitor. The author recommends using putty which can be installed using:
```
sudo apt install putty
```


