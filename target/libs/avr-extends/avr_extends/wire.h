/** 
 * @file wire.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-10-20
 * @brief Declarations for the I2C 2 wire driver
 */


#ifndef WIRE_H
#define WIRE_H


#include <stdint.h>
#include <stdbool.h>

/** 
 * @brief Initialise the wire driver
 * @param scl_freq the frequency for the serial clock
 * 
 * @return 0 on success
 */
int wire_init(uint32_t scl_freq);

/** 
 * @brief Send a write message with data to the slave
 * @param addr the address to write to 7-bit
 * @param data the data to send
 * 
 * @return 0 if successful, 1 if internal error, 2 if no ack
 */
int wire_write(uint8_t addr, uint8_t data);

// void wire_read(void);


#endif // WIRE_H