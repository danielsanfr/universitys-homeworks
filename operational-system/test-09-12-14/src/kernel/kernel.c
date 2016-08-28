#include "gdt.h"
#include "idt.h"
#include "monitor.h"
#include "timer.h"
#include "keyboard.h"
#include "paging.h"


int kmain()
{
	monitor_clear(); 

	monitor_write("Meu SO\n\n"); 
	gdt_init();

	idt_init();	

	asm volatile("sti"); 



	asm volatile ("int $0x3");
	asm volatile ("int $0x4");


	init_timer(100);

/*	init_keyboard();*/


	paging();

	while(1);

	return 1;
}

