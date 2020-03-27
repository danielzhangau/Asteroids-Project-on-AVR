/*
 * lab17-1.c
 *
 * LED Matrix SPI example
 */ 

#include <avr/io.h>
#define F_CPU 8000000L
#include <util/delay.h>

/* Function prototypes */
void spi_setup_master(void);
uint8_t spi_send_byte(uint8_t byte);

int main(void) {
	spi_setup_master();
	
	spi_send_byte(0x0F); /* Clear screen */
	_delay_ms(1000);
	
	spi_send_byte(0x10); /* Test pattern */
	_delay_ms(2000);

	spi_send_byte(0x0F); /* Clear screen */
	
	/* Take every pixel from black through to
	** bright green through to yellow through to
	** red and then back to black (off).
	*/
	while(1) {
		for(int i=0; i<= 15; i++) {
			spi_send_byte(0x00);
			for(int k=0; k<= 127; k++) {
				spi_send_byte(i*16);
			}
		}
		for(int i=0; i<= 15; i++) {
			spi_send_byte(0x00);
			for(int k=0; k <= 127; k++) {
				spi_send_byte(240+i);
			}
		}
		for(int i=0; i<= 15; i++) {
			spi_send_byte(0x00);
			for(int k=0; k <= 127; k++) {
				spi_send_byte((15-i)*16+15);
			}
		}	
		for(int i=0; i<= 15; i++) {
			spi_send_byte(0x00);
			for(int k=0; k <= 127; k++) {
				spi_send_byte(15-i);
			}
		}
	}
}

void spi_setup_master(void) {
	// Set up SPI communication as a master
	// Make the SS, MOSI and SCK pins outputs. These are pins
	// 4, 5 and 7 of port B on the ATmega324A
	DDRB |= 0b10110000;
	
	// Set the slave select (SS) line high
	PORTB |= 1<<4;
	
	// Set up the SPI control registers SPCR0 and SPSR0
	// - SPE0 bit = 1 (SPI is enabled)
	// - MSTR0 bit = 1 (Master Mode)
	SPCR0 = (1<<SPE0)|(1<<MSTR0);
	
	// Set SPR00 and SPR01 bits in SPCR0 and SPI2X0 bit in SPSR0
	// based on a clock divider of 128
	SPSR0 = 0<<SPI2X0;
	SPCR0 |= (1<<SPR10)|(1<<SPR00) ;
	
	// Take SS (slave select) line low
	PORTB &= ~(1<<4);
}

uint8_t spi_send_byte(uint8_t byte) {
	// Write out the byte to the SPDR0 register. This will initiate
	// the transfer. We then wait until the most significant byte of
	// SPSR0 (SPIF0 bit) is set - this indicates that the transfer is
	// complete. (The final read of SPSR0 followed by a read of SPDR0
	// will cause the SPIF0 bit to be reset to 0. See page 173 of the
	// ATmega324A datasheet (2018 version).)
	SPDR0 = byte;
	while((SPSR0 & (1<<SPIF0)) == 0) {
		; // wait
	}
	return SPDR0;
}

