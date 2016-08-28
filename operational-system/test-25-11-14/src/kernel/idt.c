#include "idt.h"
#include "utils.h"

#define NUM_INTERRUPTIONS 256

extern void idt_load(unsigned int); 

extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0 ();
extern void irq1 ();
extern void irq2 ();
extern void irq3 ();
extern void irq4 ();
extern void irq5 ();
extern void irq6 ();
extern void irq7 ();
extern void irq8 ();
extern void irq9 ();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();


struct idt_entry_struct {
	unsigned short base_low;
	unsigned short selector;
	unsigned char always0;
	unsigned char flags;
	unsigned short base_high;
} __attribute__((packed));


typedef struct idt_entry_struct idt_entry_t;


struct idt_ptr_struct {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));


typedef struct idt_ptr_struct idt_ptr_t;

int const DIVISION_BY_ZERO = 0;
int const DEBUG = 1;
int const NON_MASKABLE_INTERRUPT = 2;
int const BREAKPOINT = 3;
int const INTO_DETECTED_OVERFLOW = 4;
int const OUT_OF_BOUNDS = 5;
int const INVALID_OPCODE = 6;
int const NO_COPROCESSOR = 7;
int const DOUBLE_FAULT = 8;
int const COPROCESSOR_SEGMENT_OVERRUN = 9;
int const BAD_TSS = 10;
int const SEGMENT_NOT_PRESENT = 11;
int const STACK_FAULT = 12;
int const GENERAL_PROTECTION_FAULT = 13;
int const PAGE_FAULT = 14;
int const UNKNOWN_INTERRUPT = 15;
int const COPROCESSOR_FAULT = 16;
int const ALINGMENT_CHECK = 17;
int const MACHINE_CHECK = 18;
int const RESERVED_19 = 19;
int const RESERVED_20 = 20;
int const RESERVED_21 = 21;
int const RESERVED_22 = 22;
int const RESERVED_23 = 23;
int const RESERVED_24 = 24;
int const RESERVED_25 = 25;
int const RESERVED_26 = 26;
int const RESERVED_27 = 27;
int const RESERVED_28 = 28;
int const RESERVED_29 = 29;
int const RESERVED_30 = 30;
int const RESERVED_31 = 31;

int const INTERRUPT_REQUEST_0 = 32;
int const INTERRUPT_REQUEST_1 = 33;
int const INTERRUPT_REQUEST_2 = 34;
int const INTERRUPT_REQUEST_3 = 35;
int const INTERRUPT_REQUEST_4 = 36;
int const INTERRUPT_REQUEST_5 = 37;
int const INTERRUPT_REQUEST_6 = 38;
int const INTERRUPT_REQUEST_7 = 39;
int const INTERRUPT_REQUEST_8 = 40;
int const INTERRUPT_REQUEST_9 = 41;
int const INTERRUPT_REQUEST_10 = 42;
int const INTERRUPT_REQUEST_11 = 43;
int const INTERRUPT_REQUEST_12 = 44;
int const INTERRUPT_REQUEST_13 = 45;
int const INTERRUPT_REQUEST_14 = 46;
int const INTERRUPT_REQUEST_15 = 47;


idt_entry_t idt[NUM_INTERRUPTIONS]; 
idt_ptr_t  idt_ptr;


void idt_set_gate(int num_exception, unsigned long base, unsigned short selector,
					unsigned char flags)
{
	idt[num_exception].base_low = (base & 0xFFFF);
	idt[num_exception].base_high = (base >> 16) & 0xFF;

	idt[num_exception].selector = selector;
	idt[num_exception].always0 = 0;
	idt[num_exception].flags = flags;
}

void idt_init(void)
{
	idt_ptr.limit = (sizeof(idt_entry_t) * NUM_INTERRUPTIONS) - 1; 	
	idt_ptr.base  = (unsigned int) &idt;

	
	memset(&idt, 0, sizeof(idt_entry_t)*256);

	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x00);
	outb(0xA1, 0x00);

	
	idt_set_gate(DIVISION_BY_ZERO, (unsigned int) isr0, 0x10, 0x8E);
	idt_set_gate(DEBUG, (unsigned int) isr1, 0x10, 0x8E);
	idt_set_gate(NON_MASKABLE_INTERRUPT, (unsigned int) isr2, 0x10, 0x8E);
	idt_set_gate(BREAKPOINT, (unsigned int) isr3, 0x10, 0x8E);
	idt_set_gate(INTO_DETECTED_OVERFLOW, (unsigned int) isr4, 0x10, 0x8E);
	idt_set_gate(OUT_OF_BOUNDS, (unsigned int) isr5, 0x10, 0x8E);
	idt_set_gate(INVALID_OPCODE, (unsigned int) isr6, 0x10, 0x8E);
	idt_set_gate(NO_COPROCESSOR, (unsigned int) isr7, 0x10, 0x8E);
	idt_set_gate(DOUBLE_FAULT, (unsigned int) isr8, 0x10, 0x8E);
	idt_set_gate(COPROCESSOR_SEGMENT_OVERRUN, (unsigned int) isr9, 0x10, 0x8E);
	idt_set_gate(BAD_TSS, (unsigned int) isr10, 0x10, 0x8E);
	idt_set_gate(SEGMENT_NOT_PRESENT, (unsigned int) isr11, 0x10, 0x8E);
	idt_set_gate(STACK_FAULT, (unsigned int) isr12, 0x10, 0x8E);
	idt_set_gate(GENERAL_PROTECTION_FAULT, (unsigned int) isr13, 0x10, 0x8E);
	idt_set_gate(PAGE_FAULT, (unsigned int) isr14, 0x10, 0x8E);
	idt_set_gate(UNKNOWN_INTERRUPT, (unsigned int) isr15, 0x10, 0x8E);
	idt_set_gate(COPROCESSOR_FAULT, (unsigned int) isr16, 0x10, 0x8E);
	idt_set_gate(ALINGMENT_CHECK, (unsigned int) isr17, 0x10, 0x8E);
	idt_set_gate(MACHINE_CHECK, (unsigned int) isr18, 0x10, 0x8E);
	idt_set_gate(RESERVED_19, (unsigned int) isr19, 0x10, 0x8E);
	idt_set_gate(RESERVED_20, (unsigned int) isr20, 0x10, 0x8E);
	idt_set_gate(RESERVED_21, (unsigned int) isr21, 0x10, 0x8E);
	idt_set_gate(RESERVED_22, (unsigned int) isr22, 0x10, 0x8E);
	idt_set_gate(RESERVED_23, (unsigned int) isr23, 0x10, 0x8E);
	idt_set_gate(RESERVED_24, (unsigned int) isr24, 0x10, 0x8E);
	idt_set_gate(RESERVED_25, (unsigned int) isr25, 0x10, 0x8E);
	idt_set_gate(RESERVED_26, (unsigned int) isr26, 0x10, 0x8E);
	idt_set_gate(RESERVED_27, (unsigned int) isr27, 0x10, 0x8E);
	idt_set_gate(RESERVED_28, (unsigned int) isr28, 0x10, 0x8E);
	idt_set_gate(RESERVED_29, (unsigned int) isr29, 0x10, 0x8E);
	idt_set_gate(RESERVED_30, (unsigned int) isr30, 0x10, 0x8E);
	idt_set_gate(RESERVED_31, (unsigned int) isr31, 0x10, 0x8E);

	idt_set_gate(INTERRUPT_REQUEST_0, (unsigned int) irq0, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_1, (unsigned int) irq1, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_2, (unsigned int) irq2, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_3, (unsigned int) irq3, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_4, (unsigned int) irq4, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_5, (unsigned int) irq5, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_6, (unsigned int) irq6, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_7, (unsigned int) irq7, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_8, (unsigned int) irq8, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_9, (unsigned int) irq9, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_10, (unsigned int) irq10, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_11, (unsigned int) irq11, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_12, (unsigned int) irq12, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_13, (unsigned int) irq13, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_14, (unsigned int) irq14, 0x10, 0x8E);
	idt_set_gate(INTERRUPT_REQUEST_15, (unsigned int) irq15, 0x10, 0x8E);

	idt_load((unsigned int) &idt_ptr);
}

