// blink LED on port Port C (A0, A1, etc) 
#include <avr/io.h>
  
// initialize timer, interrupt and variable
void timer1_init()
{
    // set up timer with prescaler = 64 and CTC mode
    TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);
  
    // initialize counter
    TCNT1 = 0;
  
    // initialize compare value
    OCR1A = 24999;
}
  
int main(void)
{
    // connect led to pin PC0
    DDRC |= (1 << 1);
  
    // initialize timer
    timer1_init();
  
    // loop forever
    while(1)
    {
        // check whether the flag bit is set
        // if set, it means that there has been a compare match
        // and the timer has been cleared
        // use this opportunity to toggle the led
        
        if (TIFR1 & (1 << OCF1A)) // NOTE: '>=' used instead of '=='
        {
            PORTC ^= (1 << 1); // toggles the led
        }
  
        // wait! we are not done yet!
        // clear the flag bit manually since there is no ISR to execute
        // clear it by writing '1' to it (as per the datasheet)
        TIFR1 |= (1 << OCF1A);
  
        // yeah, now we are done!
    }
}

