#ifndef __TIMEING__
#define __TIMEING__

#define T 12  // Clock cycle
#define CLOCK 11059200 // Master clock frequency
#define US CLOCK/T/1000/1000
#define MS CLOCK/T/1000

#ifndef TRUR
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

long time = 0;
bit block = TRUE;
int duration = 65535 - 1 * US;


void timer0_isr() interrupt 1 using 1{
    TL0 = duration;
    TH0 = duration >> 8;
    block = FALSE;
}

void set_timer0() {
    TMOD = 0x01; //set timer1 as mode1 (16-bit)
    TL0 = duration; //initial timer1 low byte
    TH0 = duration >> 8; //initial timer1 high byte
    TR0 = 1; //timer1 start running
    ET0 = 1; //enable timer1 interrupt
    EA = 1; //open global interrupt switch
}

void clear_timer0() {
    TR0 = 0;
    ET0 = 0;
    EA = 0;
}

void blocking_us(int us) {
    if (US < 1)
        duration = 65535 - us * 1;
    else 
        duration = 65535 - us * US;
    block = TRUE;
    set_timer0();
    while(block);
    clear_timer0();
}

void blocking_ms(int ms) {
    duration = 65535 - ms * MS;
    block = TRUE;
    set_timer0();
    while(block);
    clear_timer0();
}

void blocking_s(int s) {
    int i = s * 1000;
    for(; i > 0; i--) 
        blocking_us(1000);
    /*
    int i = s * 1000 / 50;
    for(; i > 0; i--) 
        blocking_ms(50);
    */
}
#endif