/***************************************************************************
 * Lab07.c (barebones starter code version)
 *
 *   Created:
 *    Author:
 * Processor: ATmega128A (on a ReadyAVR)
 *
 * Your comments go here...
 *
 **************************************************************************/

/* your #include file declaration(s) go here */
#include "UARTLibrary.h"

/* your #define declarations go here */
#define BaudRate 9600
#define DataBits 8
#define StopBits 1
#define NoParity 0

// prototype subroutine definitions
void initializeArray(unsigned char *cp);
void displayArray(unsigned char *cp);
void updateArray(unsigned char *cp);

int main(void)
{
	// create a 61-char array
	unsigned char cellArray[61];
	initializeArray(&cellArray[0]);
	// Initialize the UART
	// ProfNote:  Understand the UARTLibary.h before blindly running the next line!
	uart_init(BaudRate, DataBits, StopBits, NoParity);
	
    for (int i = 0; i < 122; i++){
		displayArray(&cellArray[0]); 
		updateArray(&cellArray[0]);
	}
	while(1){
	}
}

void initializeArray(unsigned char *cp){
	unsigned char src[] = "                              *                              ";
	memcpy(cp, src, 61);
}
void displayArray(unsigned char *cp){
	// ProfNote:  Look through your line using "uart_tx(<char>)" to print one character at a time.
	// At the end of the line, use "uart_tx('\r'); uart_tx('\n');" to print a new line to keep your
	// output aligned properly.
	for (int i=0; i < 61; i++){
		if (i == 60){
			uart_tx(*cp);
			uart_tx('\r'); 
			uart_tx('\n');
		}else{
			uart_tx(*cp);
			cp++;
		}
	}
}
void updateArray(unsigned char *cp){
	unsigned char nextArray[61];
	nextArray[0] = ' ';
	nextArray[60] = ' ';
	unsigned char *np = &nextArray[1];
	for (int i=1; i<60; i++){	
		if ((*(cp+i) == ' ') && (*(cp+1+i) == '*') && (*(cp-1+i) == ' ')){
			*np = '*';
		}else if((*(cp+i) == '*') && (*(cp+1+i) == '*') && (*(cp-1+i) == ' ')){
			*np = '*';
		}else if ((*(cp+i) == ' ') && (*(cp-1+i) == '*') && (*(cp+1+i) == ' ')){
			*np = '*';
			}else{
			*np = ' ';
		}
		np++;
	}
	memcpy(cp, nextArray, 61);
}
