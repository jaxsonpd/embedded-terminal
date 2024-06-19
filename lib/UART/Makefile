## 
# @file Makefile
# @author Jack Duignan (JackpDuigna@gmail.com)
# #date 2024-07-19
# @brief the make file for the UART library

MMCU = atmega328p
CPUFREQ = 16000000UL

# Flags
CFLAGS = -Os -DF_CPU=$(CPUFREQ) -mmcu=$(MMCU) -Wall -Wstrict-prototypes -Wextra

# Commands
CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm
MKDIR_P = mkdir -p

BUILDDIR = ./build
SRCDIR = ./

SRCS := $(shell find $(SRCDIR) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILDDIR)/%.o)

all: $(BUILDDIR)/UART.c.o

# Create object files
$(BUILDDIR)/%.c.o: $(SRCDIR)/%.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ 

# Clean
.PHONY: clean
clean:
	$(DEL) -rf $(BUILDDIR)