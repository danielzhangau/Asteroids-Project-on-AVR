/*
 * score.c
 *
 * Written by Peter Sutton
 */

#include "score.h"
#include "terminalio.h"
#include <avr/pgmspace.h>
#include <stdio.h>
#include <avr/io.h>

// Seven segment display - segment values for digits 0 to 9

int32_t score;

void init_score(void) {
	score = 0;
}

void add_to_score(int16_t value) {
	score += value;
	
	if (score <= 0) {
		score = 0;
	}
}

uint32_t get_score(void) {
	return score;
}

void display_score(void) {
	move_cursor(10,10);
	printf_P(PSTR("Scores: %8d"), get_score());
}


