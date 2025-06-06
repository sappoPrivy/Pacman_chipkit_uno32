/*display.c
	Created by Tenzin Sangpo Choedon
*/

#include <stdint.h>
#include <pic32mx.h>
#include "functions.h"

/*This static display buffer will be used to manipulate pixels*/
static int8_t data_buffer[DISPLAY_COLUMNS][DISPLAY_PAGES];

/*BEGGINING OF COPIED CODE*/

void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

void display_init(void) {
    COMMAND_MODE;
	quicksleep(10);
	ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	ACTIVATE_RESET;
	quicksleep(10);
	DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}
/*END OF COPIED CODE*/

/* Set the pixel on the display */
void display_set(int column, int row, int pixelValue){

    // The Bit offset is the bit nr in the page which correpsonds to the lower 3 bits of the row
	int bitOffset;

    // The page number is the row divided by 8 since page size is 8 bits
    int pageNr;

    /* Check that the column and row is in the correct range of the display */
    if((column < DISPLAY_COLUMNS && column >= 0) && (row < DISPLAY_ROWS && row>=0)){
        pageNr = row >> 3;
        bitOffset = row & 0x07;

        // Clear the pixel
	    data_buffer[column][pageNr] &= ~(1 << bitOffset);

	    // Set the pixel
	    data_buffer[column][pageNr] |= (pixelValue ? 1 : 0) << bitOffset;
    }	
}

/* Write to the display screen */
void display_update(void)
{      
    int currentPage, currentColumn;

	for(currentPage = 0; currentPage < DISPLAY_PAGES; ++currentPage)
	{
		COMMAND_MODE;

		// Set the page command
		spi_send_recv(0x22);

		// Set the page number 
		spi_send_recv(currentPage);

		// Set the column to start from the left column
		spi_send_recv(0x00);
		spi_send_recv(0x10);
		
		DATA_MODE;
		
		/* Write each data byte to data buffer */
		for(currentColumn = 0; currentColumn < DISPLAY_COLUMNS; ++currentColumn)
		{
			spi_send_recv(data_buffer[currentColumn][currentPage]);
		}
	}
}

/* Set text on the display */
void display_text(int line, char const *s, int offset)
{
	int i;

	/*Offset and line is within range*/
	if((offset >= 0 && offset < DISPLAY_COLUMNS) && (line >= 0 && line < DISPLAY_PAGES) ){
		/*Check every character*/
		while(*s)
		{
			int c = *s;
			/*Each character has 8 bytes*/
			for(i = 0; i < 8 && offset < DISPLAY_COLUMNS; ++i)
			{
				// The character is represented in font
				data_buffer[offset++][line] = font[c*8 + i];
			}
			++s;
		}
	}
}

/* Clear the data buffer*/
void display_clear(){
	int currentPage, currentColumn;
	for(currentPage = 0; currentPage < DISPLAY_PAGES; ++currentPage)
	{
		for(currentColumn = 0; currentColumn < DISPLAY_COLUMNS; ++currentColumn)
		{
			// Clear each byte in the page
			data_buffer[currentColumn][currentPage] = 0;
		}
	}
}


/* Convert integer to char */
void itocharconv(int number, char *buffer)
{
	// Handle negative numbers
	if( number < 0) {
		number = -number;
		buffer++;
		*(buffer) = '-';
	}

	// Determine the length
	int length = number;

	length /= 10;
	buffer++;

	while(length) {
		length /= 10;
		buffer++;
	}

	// Null terminate the string
	*(buffer--) = '\0';
	
	*(buffer--) = number % 10 + '0';
    number /= 10;

	// Write digits to the buffer
    while (number) {
        *(buffer--) = number % 10 + '0';
        number /= 10;
    }

}



