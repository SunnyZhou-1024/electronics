#include <reg51.h>
#include "common.h"
#include "SingleWireProtocol.h"
#include "time.h"
#include "BCDSegmentLED.h"

sbit p10 = P1^0;
sbit p11 = P1^1;
sbit p12 = P1^2;
sbit p13 = P1^3;
sbit p15 = P1^5;
sbit p25 = P2^5;


void main() {
    signed short temp = 0;
    unsigned char bcd[3] = {0};
    p25 = 0;
    /*
    p10 = 0;
    p11 = 0;
    p12 = 0;
    p13 = 0;
    blocking_s(1);
    p10 = 1;
    blocking_s(2);
    p11 = 1;
    blocking_s(3);
    p12 = 1;
    blocking_s(4);
    p13 = 1; 
    
    
    

    */
    while(TRUE) {  
        temp = read_ds18b20();
        if (temp > 30 ) {
            p25 = 1;
        } else {
            p25 = 0;
        }
        bcd[0] = temp / 10;
        bcd[1] = temp % 10;
        bcd[2] = 5;
        
        show(bcd);
        
        //P3 = temp;
    }
}