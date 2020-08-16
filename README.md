# Asteroids-Project-on-AVR
UQ csse2010 C introduction mainly on AVR 计算机处理器

Introduction to digital logic & digital systems; machine level representation of data; computer organization; memory system organization & architecture; interfacing & communication; microcontroller architecture and usage; programming of microcontroller based systems.

# Project Description:
The program is a simple version of Asteroids. The AVR ATmega324A microcontroller runs the program and receives input from a number of sources and outputs a display to an LED display board, with additional information being output to a serial terminal and – to be implemented as part of this project – a seven segment display and other LEDs.
- project.c – this is the main file that contains the event loop and examples of how timebased events are implemented. You should read and understand this file.
- game.h/game.c – this file contains the implementation of the operations (e.g. movements) in the game. You should read this file and understand what representation is used for the game. You will need to modify this file to add required functionality.
- buttons.h/buttons.c – this contains the code which deals with the IO board push buttons. It sets up pin change interrupts on those pins and records rising edges (buttons being pushed).
- ledmatrix.h/ledmatrix.c – this contains functions which give easier access to the services provided by the LED matrix. It makes use of the SPI routines implemented in spi.c
- pixel_colour.h – this file contains definitions of some useful colours
- score.h/score.c – a module for keeping track of and adding to the score. This module is not used in the provided code.
- scrolling_char_display.h/scrolling_char_display.c – this contains code which provides a scrolling message display on the LED matrix board.
- serialio.h/serialio.c – this file is responsible for handling serial input and output using interrupts. It also maps the C standard IO routines (e.g. printf() and fgetc()) to use the serial interface so you are able to use printf() etc for debugging purposes if you wish. You should not need to look in this file, but you may be interested in how it works and the buffer sizes used for input and output (and what happens when the buffers fill up).
- spi.h/spi.c – this file encapsulates all SPI communication. Note that by default, all SPI communication uses busy waiting – the “send” routine returns only when the data is sent. If you need the CPU cycles for other activities, you may wish to consider converting this to interrupt based IO, similar to the way that serial IO is handled.
- terminalio.h/terminalio.c – this encapsulates the sending of various escape sequences which enable some control over terminal appearance and text placement – you can call these functions (declared in terminalio.h) instead of remembering various escape sequences. Additional information about terminal IO will be provided on the course Blackboard site.
- timer0.h/timer0.c – sets up a timer that is used to generate an interrupt every millisecond and update a global time value.

How it looks like on digital board:
![GUI](https://github.com/danielzhangau/CSSE2010-c-introduction/blob/master/CSSE2010Project/CSSE2010_CSSE7201_2019_project%20-%20with%20clarifications.jpg?raw=true)

# What I learned:
- C programming
- C programming for the AVR
- The Atmel Studio environment
