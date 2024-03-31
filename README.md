# Embedded Terminal

This is a terminal designed to run on the avr series of micro controller which offers some basic functions.

# Documentation
## Commands

`help`: View the available commands and get general information about the system.

# Setup

A full installation and setup process can be found in SETUP.md

## Monitoring the Serial Port
### Serial monitor settings

| Setting | Value |
| ------ | --------- |
| EOL sent | `\n` |
| EOL reciving | `\n` |
| Baud Rate | `9600` |
| Encoding | `8n1` |

### Installation
The author recommends using putty which can be installed using:
```
sudo apt install putty
```

To monitor the serial port on linux terminal use screen this requires some setup:

Ensure screen is installed using:

```
sudo apt install screen
```

Then add the user to the dialout group using:

```
sudo usermod -a -G dialout $USER
```

Then launch screen using:

```
screen [DEVICE NAME] [BAUDRATE]
```
