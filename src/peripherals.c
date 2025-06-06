/*Peripherals.c
    Created by Tenzin Sangpo Choedon
*/

#include <stdint.h>
#include "functions.h"
#include <pic32mx.h>

/* The following show what each button corresponds to
 * in menu BTN4 - First Option, BTN3 - Second option
 * in game BTN1 - Right, BTN2 - Down, BTN3 - Up, BTN4 - Left
 */
#define TMR2PERIOD (80000000 / 256)/10

void buttons_init(){
    // PORTD in bits <7:5> has BTN2, BTN3, BTN4
	TRISDSET = 0x3 << 5;
	// PORTF in bit 1 has BTN1
	TRISFSET = 0x01 << 1;
}

int8_t get_buttons() {
	/* Collect info on buttons */
	volatile int8_t btnInfo = 0;
    // Extract bits <7:5> for BTN2, BTN3, BTN4
    btnInfo |= (PORTD & 0xe0) >> 4;
    // Extract bit 1 for BTN1
    btnInfo |= (PORTF & 0x2) >> 1;
    return btnInfo;
}

void timer_init() {
    // Initialize timer 2
	// Vi testade med 0x60 som är 1:64 men den var för snabb
	// Prescaling 1:256 motsvarar 0111 0000 i bits
	T2CON = 0x70;
	// Set the period register
	PR2 = TMR2PERIOD;
	// Reset the timer
	TMR2 = 0;
	// Start the timer, ON bit is bit 15, set it to 1
	T2CONSET = 0x8000;
}

void spi_init() {
    /*BEGINNING OF COPIED CODE*/
    /* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
    SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
    /*END OF COPIED CODE*/
}

void peripherals_init(){
    /*BEGINNING OF COPIED CODE*/
    SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
    /*END OF COPIED CODE*/
}

void interrupt_init(){
    // Initialize interrupt routine
    // Values between 4 and 31 will work for bits 4 - 2 which corresponds to T2IP
    // T2IP for priority is bit 4-2 and T2IS for sub priority is bit 1-0
    IPC(2) = 4;
    // T2IE for enabling timer 2 interrupt is bit 8 in IEC(0)
    // Set to 1 to enable interrupt on bit 8
    IEC(0)= 0x100;
    // Enable interrupts globally
    enable_interrupt();
}