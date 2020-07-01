#ifndef __ONE_WIRE_PROTOCOL__
#define __ONE_WIRE_PROTOCOL__

#include <reg51.h>
#include "time.h"

#ifndef TRUR
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

sbit DQ = P2^4;

int blocking = 0;

void write_0() {
    DQ = 0;
    blocking_us(80);
    DQ = 1;
    blocking_us(10);
}


void write_1() {
    DQ = 0;
    blocking++;
    blocking++;
    DQ = 1;
    blocking_us(80);
}

unsigned char read_bit() {
    unsigned char value = 0;
    DQ = 1;
    blocking_us(10);
    DQ = 0;
    blocking++;
    blocking++;
    DQ = 1;
    blocking++;
blocking++;blocking++;blocking++;
    value = DQ;
    blocking_us(60);
    return value;
}

unsigned char read_byte() {
    unsigned char i = 8;
    unsigned char byte = 0;
    for (; i > 0; i--) {
        byte >>= 1;
        byte |= (read_bit() << 7);
    }
    return byte;
}

void write(unsigned char byte) {
    signed char i = 8;
    for (; i>0; i--) {
        if (byte & 0x01) {
            write_1();
        } else {
            write_0();
        }
        byte >>= 1;
    }
}


void init() {
    DQ = 1;
    blocking_us(10);
    DQ = 0;
    blocking_us(480);
    DQ = 1;
    blocking_us(30);
    while (DQ) {
        blocking_us(30);
    }
    blocking_us(480);
}

signed short read_ds18b20() {
    unsigned char cs[9] = {0};
    signed char i = 9;
    signed short temp = 0;
/*    init();
    write(0xcc);
    write(0x4e);
    write(0x07);
    write(0xba);
    write(0x7f); */
    
    // Issue temperature convert command
    init();
    write(0xcc); // Skip ROM, if there are more than one 1-wire device represence, we should try to match ROM
    write(0x44); // Convert temperature
    blocking_us(500); 
    while (!DQ); // Slave will pull low the bus while conducting conversion
    init();
    write(0xcc);
    write(0xBE); // Read Scratchpad
    for (; i>0; i--) {
        cs[i-1] = read_byte(); 
    }
    temp = temp | (cs[8] >> 4);
    temp = temp | (cs[7] << 4);
    return temp;
}

#endif