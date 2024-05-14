#ifndef SR_74HC595
#define SR_74HC595

#include <stdbool.h>
#include <stdint.h>

#ifndef SR_DATA
#define SR_DATA 11
#endif

#ifndef SR_CLK
#define SR_CLK 12
#endif

#ifndef SR_LATCH
#define SR_LATCH 8
#endif

#define _SRMASK 0x0001

void sr_init(); //init the pins set as SR_DATA, SR_CLK, SR_LATCH
void sr_set(uint16_t _srreg); //set 16 bits and output them

#endif