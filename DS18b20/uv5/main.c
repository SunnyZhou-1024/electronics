#include <reg51.h>
#include "SingleWireProtocol.h"
#include "time.h"

sbit p10 = P1^0;
sbit p11 = P1^1;
sbit p12 = P1^2;
sbit p13 = P1^3;

void main() {
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
    while(TRUE);
}