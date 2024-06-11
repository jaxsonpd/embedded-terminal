## 
# @file Makefile
# @author Jack Duignan (JackpDuigna@gmail.com)
# #date 2024-06-11
# @brief the make file for the embedded-terminal project

USBDEVICE = /dev/ttyUSB0

CC = avr-gcc
CFLAGS = -Os -DF_CPU=16000000UL -mmcu=atmega328p -Wall -Wstrict-prototypes -Wextra

OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm

SRCDIR = .
LIBDIR = ../lib
BUILDDIR = $(SRCDIR)/build

_DEPS 

# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
