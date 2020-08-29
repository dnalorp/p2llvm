/*
  This tests structs and passing byvals into and out of functions. more datatypes are intruduced as well,
  a simple propeller library is created, and crt0 is created to load multiple cogs with parameters passed to the code
  a make file is introduced to build and link everything

  compilation:
    make
*/

#define P2_TARGET_MHZ   200
#include "propeller2.h"
#include "sys/p2es_clock.h"

volatile unsigned int blink1_stack[32];
volatile unsigned int blink2_stack[32];

struct led_mb_t {
    char pin;
    int delay;
};

void blink(void *par) {
    // led_mb_t *led = (led_mb_t*)par;

    // dirh(led->pin);

    // while(1) {
    //     outl(led->pin);
    //     waitx(led->delay);
    //     outh(led->pin);
    //     waitx(led->delay);
    // }

    led_mb_t *led = (led_mb_t*)par;

    dirh(56);

    while(1) {
        outl(56);
        waitx(20000000);
        outh(56);
        waitx(20000000);
    }

}

led_mb_t modify_led_mb(led_mb_t l) __attribute__((noinline));

led_mb_t modify_led_mb(led_mb_t l) {
    if (l.pin == 56) {
        l.pin = 57;
    } else {
        l.pin = 58;
    }

    if (l.delay == _CLOCKFREQ) {
        l.delay = _CLOCKFREQ/2;
    }

    return l;
}

int main() {

    //waitx(12500000);
    //_clkset(_SETFREQ, _CLOCKFREQ);

    //led_mb_t led1;
    //led_mb_t led2;

    //led1.pin = 56;
    //led1.delay = _CLOCKFREQ;
    //led2 = modify_led_mb(led1);

    _cognew(blink, 0, (unsigned int*)blink1_stack);
    //_cognew(blink, (int)&led2, (unsigned int*)blink2_stack);

    while(1);

    return 0;
}