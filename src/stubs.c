/* stubs.c
 * This file written 2015 by Axel Isaksson
 * This copyright notice added 2015 by F Lundevall*/

/*BEGINNING OF COPIED CODE*/
//Non-Maskable Interrupt; something bad likely happened, so hang 
void _nmi_handler() {
	for(;;);
}

// This function is called upon reset, before .data and .bss is set up 
void _on_reset() {
	
}

// This function is called before main() is called, you can do setup here
void _on_bootstrap() {
	
}
/*END OF COPIED CODE*/
