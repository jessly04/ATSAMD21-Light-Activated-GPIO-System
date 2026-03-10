#include <xc.h>

#define LED_PIN      (1 << 6) //LED ON PA06

#define LDR_PIN      (1 << 5) // PHOTO-SENSOR ON PA05

void delay_ms(int ms) {
    for (volatile int i = 0; i < ms * 200; i++);
}

int main(void) {
    PM_REGS->PM_APBBMASK |= (1 << 3); //ENABLE PORT APB CLOCK - automatically at bit 3 

    PORT_REGS->GROUP[0].PORT_DIRSET = LED_PIN; // setting LED as output (sec 23.8.3) if high, configured as output

    PORT_REGS->GROUP[0].PORT_DIRCLR = LDR_PIN; // setting LDR as input (sec 23.8.2) if high, configured as input

    // Enable internal pull-up:   
    PORT_REGS->GROUP[0].PORT_PINCFG[5] |= (1 << 2) | (1<<1); // enable pull resistor (sec: 23.8.13) 0000 0100 - PULLEN, 0000 0001 - INEN)

    PORT_REGS->GROUP[0].PORT_OUTSET = LDR_PIN; // writing "1" to OUTSET will make pin pull-up (sec: 23.8.7) input connected to internal pull-up

    // loop will read PA05 and drive PA06 
    while (1) {
        unsigned int in = PORT_REGS->GROUP[0].PORT_IN; // reads input register

        // OUTCLR & OUTSET 
        if (in & LDR_PIN) {
            // when PA05 = 1 (LDR_PIN) then bright light, pull-up holds it high),
            // turn LED off:
            PORT_REGS->GROUP[0].PORT_OUTCLR = LED_PIN; // clear bits to drive output low (OUTCLR makes pin pull-down) (sec 23.8.6)
        } else {
            // When PA05 = 0 (LDR_PIN) then dark, photoresistor pulls it low),
            // turn LED on:
            PORT_REGS->GROUP[0].PORT_OUTSET = LED_PIN; // set bits to drive output high (OUTSET makes pin pull-up))
        }

        // small delay for visible LED response
        delay_ms(50);
    }

    return 0;
}
