/*
 * timer0.c
 *
 * Author: Peter Sutton
 *
 * We setup timer0 to generate an interrupt every 1ms
 * We update a global clock tick variable - whose value
 * can be retrieved using the get_clock_ticks() function.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer0.h"
#include "score.h"

/* Our internal clock tick count - incremented every 
 * millisecond. Will overflow every ~49 days. */
static volatile uint32_t clockTicks;
uint8_t seven_seg[10] = { 63,6,91,79,102,109,125,7,127,111};
uint8_t number;
uint8_t digit = 0;
uint8_t value;
uint8_t isPause = 0;

/* Set up timer 0 to generate an interrupt every 1ms. 
 * We will divide the clock by 64 and count up to 124.
 * We will therefore get an interrupt every 64 x 125
 * clock cycles, i.e. every 1 milliseconds with an 8MHz
 * clock. 
 * The counter will be reset to 0 when it reaches it's
 * output compare value.
 */
void init_timer0(void) {
	/* Reset clock tick count. L indicates a long (32 bit) 
	 * constant. 
	 */
	clockTicks = 0L;
	
	/* Clear the timer */
	TCNT0 = 0;

	/* Set the output compare value to be 124 */
	OCR0A = 124;
	
	/* Set the timer to clear on compare match (CTC mode)
	 * and to divide the clock by 64. This starts the timer
	 * running.
	 */
	TCCR0A = (1<<WGM01);
	TCCR0B = (1<<CS01)|(1<<CS00);

	/* Enable an interrupt on output compare match. 
	 * Note that interrupts have to be enabled globally
	 * before the interrupts will fire.
	 */
	TIMSK0 |= (1<<OCIE0A);
	
	/* Make sure the interrupt flag is cleared by writing a 
	 * 1 to it.
	 */
	TIFR0 &= (1<<OCF0A);
}

uint32_t get_current_time(void) {
	uint32_t returnValue;

	/* Disable interrupts so we can be sure that the interrupt
	 * doesn't fire when we've copied just a couple of bytes
	 * of the value. Interrupts are re-enabled if they were
	 * enabled at the start.
	 */
	uint8_t interruptsOn = bit_is_set(SREG, SREG_I);
	cli();
	returnValue = clockTicks;
	if(interruptsOn) {
		sei();
	}
	return returnValue;
}

ISR(TIMER0_COMPA_vect) {
	/* Increment our clock tick count */
	if (isPause == 0) {
		clockTicks++;
	}

	DDRA = 0xFF;
	DDRD = (1<<PORTD5);	
	int LeftValue = get_score() % 10;
	int RightValue = (get_score() / 10) % 10;
	//while(1) {
	/* Output the current digit */
	if (get_score() < 10) {
		PORTD = (0<<PORTD5);	
		PORTA = seven_seg[LeftValue];
	}
	else {
		if(digit == 0) {
			/* Extract the ones place from the timer counter 0 value */
			/* HINT: Consider the modulus (%) operator. */
			PORTA = 0;
			PORTD = (0<<PORTD5);
			PORTA = seven_seg[LeftValue];
		} else {
			/* Extract the tens place from the timer counter 0 */
			PORTA = 0;
			PORTD = (1<<PORTD5);
			PORTA = seven_seg[RightValue];
		}
	}
	/* Change the digit flag for next time. if 0 becomes 1, if 1 becomes 0. */
	digit = 1 - digit;

	//}
}

void pause_clock() {
	isPause = 1;
}

void unpause_clock() {
	isPause = 0;
}