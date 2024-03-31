# Embedded Terminal

This is a terminal designed to run on the avr series of micro controller which offers some basic functions.

# Documentation
## Commands

# Setup

A full installation and setup process can be found in SETUP.md

## Monitoring the Serial Port

To monitor the serial port on linux use screen this requires some setup:

### Serial monitor settings

| Setting | Value |
| ------ | --------- |
| EOL sent | `\n` |
| EOL reciving | `\n` |
| Baud Rate | `9600` |
| Encoding | `8n1` |

### Installation
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

Or use putty:

```
sudo apt install putty
```