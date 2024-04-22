## 
# @file Makefile
# @author Jack Duignan (JackpDuigna@gmail.com)
# 2024-03-30
# @brief various functions to make the project

CC = avr-gcc
CFLAGS = -Os -DF_CPU=16000000UL -mmcu=atmega328p -Wall -Wstrict-prototypes -Wextra
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm
SRCDIR = src
INCDIR = src/include

USBDEVICE = /dev/ttyUSB0



# Default Target
all: main.out

# Compile the object files
main.o: $(SRCDIR)/main.c $(SRCDIR)/command.h $(SRCDIR)/utils.h $(INCDIR)/UART.h $(INCDIR)/GPIO.h
	$(CC) -c $(CFLAGS) $< -o $@

UART.o: $(INCDIR)/UART.c $(INCDIR)/UART.h
	$(CC) -c $(CFLAGS) $< -o $@

command.o: $(SRCDIR)/command.c $(SRCDIR)/command.h $(INCDIR)/UART.h
	$(CC) -c $(CFLAGS) $< -o $@

help.o: $(SRCDIR)/help.c $(SRCDIR)/help.h $(INCDIR)/UART.h
	$(CC) -c $(CFLAGS) $< -o $@

clear.o: $(SRCDIR)/clear.c $(SRCDIR)/clear.h $(INCDIR)/UART.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: $(SRCDIR)/led.c $(SRCDIR)/led.h $(INCDIR)/UART.h
	$(CC) -c $(CFLAGS) $< -o $@

utils.o: $(SRCDIR)/utils.c $(SRCDIR)/utils.h
	$(CC) -c $(CFLAGS) $< -o $@

GPIO.o: $(INCDIR)/GPIO.c $(INCDIR)/GPIO.h
	$(CC) -c $(CFLAGS) $< -o $@

main.out: main.o UART.o command.o help.o clear.o led.o GPIO.o utils.o
	$(CC) -mmcu=atmega328p $^ -o $@




# Clean the project
.PHONY: clean
clean:
	$(DEL) *.o *.out *.hex

# Flash to the MCC
.PHONY: flash
flash: main.out
	$(OBJCOPY) -O ihex -R .eeprom main.out main.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P $(USBDEVICE) -b 115200 -U flash:w:main.hex
	$(SIZE) main.hex


# Launch a serial prompt
.PHONY: serial
serial: 
	putty -serial $(USBDEVICE) -sercfg 8,'1',9600,'n' -fn "Monospace 13"
