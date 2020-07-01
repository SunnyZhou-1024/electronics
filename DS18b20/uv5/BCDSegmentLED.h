#include <reg51.h>
#include "time.h"

sbit s1 = P2^0;
sbit s2 = P1^1;
sbit s3 = P1^0;
sbit dot = P3^6;

void timer1_hook();

void timer1_isr() interrupt 3 {
    TL1 = 65535 - MS;
    TH1 = (65535 - MS) >> 8;
    timer1_hook();
}

unsigned char bcd[10] = {
    0x00,
    0x01
};

void BCD(unsigned char bcd) {
    unsigned char temp = 0xc3 & P1;
    P1 = 0;
    P1 = P1 | (bcd << 2);
    P1 |= temp;
}

void select(unsigned char which) {
    s1 = which & 0x01;
    s2 = which & 0x02;
    dot = !(which & 0x02);
    s3 = which & 0x04;
}
void timer1_hook() {
    
}


void show(unsigned char bcd[3]) {
    BCD(bcd[2]);
    select(0x01);
    blocking_ms(5);
    BCD(bcd[1]);
    select(0x02);
    blocking_ms(5);
    BCD(bcd[0]);
    select(0x04);
    blocking_ms(15);
}