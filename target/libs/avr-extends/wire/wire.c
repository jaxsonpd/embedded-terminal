/** 
 * @file i2c.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-10-20
 * @brief Definitions for the I2C 2 wire driver
 */


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <avr/io.h>

#include "../avr_extends/wire.h"

#define START_SENT 0x08
#define STARTR_SENT 0x10

#define ADDRESS_ACK 0x18
#define DATA_ACK 0x28

int wire_init(uint32_t scl_freq) {
    // Calculate TWI interface speed
    int TWBR_value = (F_CPU-scl_freq*16UL) / (2*scl_freq*1);  
    printf("TWBR value: %d\r\n", TWBR_value);
    TWBR = TWBR_value;

    return 0;
}

int wire_write(uint8_t addr, uint8_t data) {
    // Enable two wire interface clear interrupt 
    // and send a start condition
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

    // Wait for start condition to occur and check correct
    while (!(TWCR&(1<<TWINT))); 

    if (((TWSR & 0xF8)!= START_SENT) && ((TWSR & 0xF8)!= STARTR_SENT)) {
        return 1;
    }

    // load the address with a write cmd and trigger a send
    TWDR = addr << 1;
    printf("addr: %d\r\n", addr);
    TWCR = (1<<TWINT)|(1<<TWEN);

    // Wait for addr to send and check acknowledge
    while (!(TWCR&(1<<TWINT))); 

    if ((TWSR & 0xF8)!= ADDRESS_ACK) {
        return 2;
    }

    // Load and send data
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);

    // Wait for data to send and check acknowledge
    while (!(TWCR&(1<<TWINT))); 

    if ((TWSR & 0xF8)!= DATA_ACK) {
        return 3;
    }

    // Send stop
    TWCR = (1<<TWINT)|(1<<TWSTO);

    return 0;
}
