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

void write_0() {
    DQ = 0;
    blocking_us(80);
    DQ = 1;
    blocking_us(10);
}


void write_1() {
    DQ = 0;
    blocking_us(2);
    DQ = 1;
    blocking_us(80);
}

signed char read_bit() {
    int value = 0;
    DQ = 0;
    blocking_us(2);
    DQ = 1;
    blocking_us(15);
    value = DQ;
    
    blocking_us(70);
    return value;
}

signed char read_byte() {
    int i = 8;
    signed char byte = 0;
    for (; i > 0; i--) {
        byte |= read_bit();
        byte <<= 1;
    }
    return byte;
}

void write(signed char byte) {
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
    int presence = FALSE;
    DQ = 0;
    blocking_us(480);
    DQ = 1;
    blocking_us(30);
    while (!presence) {
        blocking_us(30);
        presence = DQ;
    }
    blocking_us(480);
    //P1 = 170;
}

signed short read_ds18b20() {
    signed char cs[] = {0};
    signed char i = 9;
    signed short temp = 0;
    /*init();
    write(0xcc);
    write(0x4e);
    write(0x07);
    write(0xba);
    write(0x7f); */
    init();
    write(0xcc);
    write(0xbe);
    for (; i>0; i--) {
        cs[i-1] = read_byte();
    }
    temp = temp | (cs[8] << 4);
    temp = temp | (cs[7] >> 4);
    return cs[8];
}

#endif