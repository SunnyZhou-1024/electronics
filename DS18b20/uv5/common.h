#ifndef __COMMON__
#define __COMMON__

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


#endif