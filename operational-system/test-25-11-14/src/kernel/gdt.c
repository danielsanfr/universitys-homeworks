#include "gdt.h"

#define NUM_SEGMENTS 3

extern void gdt_load(unsigned int); 

struct gdt_entry_struct {
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));


typedef struct gdt_entry_struct gdt_entry_t;


struct gdt_ptr_struct {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));


typedef struct gdt_ptr_struct gdt_ptr_t;


int const NULL_SEGMENT = 0;
int const DATA_SEGMENT = 1;
int const CODE_SEGMENT = 2;

gdt_entry_t gdt[NUM_SEGMENTS]; 
gdt_ptr_t  gdt_ptr;


void gdt_add_seg(int num_segment, unsigned long base, unsigned long limit, 
		unsigned char access, unsigned char granularity)
{
	gdt[num_segment].base_low = (base & 0xFFFF);
	gdt[num_segment].base_middle = (base >> 16) & 0xFF;
	gdt[num_segment].base_high = (base >> 24) & 0xFF;
 
	gdt[num_segment].limit_low = (limit & 0xFFFF);
	gdt[num_segment].granularity = ((limit >> 16) & 0x0F);
 
	gdt[num_segment].granularity |= (granularity & 0xF0);
	gdt[num_segment].access = access;
}

void gdt_init(void)
{
	gdt_ptr.limit = (sizeof(gdt_entry_t) * NUM_SEGMENTS) - 1; 	
	gdt_ptr.base  = (unsigned int) &gdt;

	gdt_add_seg(NULL_SEGMENT, 0, 0, 0, 0);		   
	gdt_add_seg(DATA_SEGMENT, 0, 0xFFFFFFFF, 0x92, 0xCF); 
	gdt_add_seg(CODE_SEGMENT, 0, 0xFFFFFFFF, 0x9A, 0xCF);  

	gdt_load((unsigned int) &gdt_ptr);
}

