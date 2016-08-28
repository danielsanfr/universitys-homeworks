
// Estrutura para apontar para a GDT
struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

// Definicoes das funcoes
extern void gdt_load(int);
void kmain();
void gdt_init();
//void gdt_add_seg(int, int, int, int);
void hang();

kmain()
{
	gdt_init();
	hang();
}

// Estrutura que representa um segmento
struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

// Implementacao do loop
void hang()
{
	while(1);
}

gdt_init()
{
	//__asm__ __volatile__ ("xchg %bx, %bx");

	// Tabela GDT
	struct gdt_entry gdt[3];
	
	struct gdt_ptr gp;
	gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
	gp.base = &gdt;
	
	gdt_add_seg(gdt, 0, 0, 0, 0, 0);
	gdt_add_seg(gdt, 1, 0, 0xFFFFFFFF, 0xCF, 0x92);
	gdt_add_seg(gdt, 2, 0, 0xFFFFFFFF, 0xCF, 0x9A);
	
	//__asm__ __volatile__ ("xchg %bx, %bx");
	
	gdt_load(&gp);
	
	//__asm__ __volatile__ ("xchg %bx, %bx");
}

gdt_add_seg(struct gdt_entry *gdt, int index, int base, int size, int ring, int type)
{
	gdt[index].base_low 	= (base & 0xFFFF);
    gdt[index].base_middle 	= (base >> 16) & 0xFF;
    gdt[index].base_high 	= (base >> 24) & 0xFF;

    gdt[index].limit_low 	= (size & 0xFFFF);
    gdt[index].granularity 	= ((size >> 16) & 0x0F);

    gdt[index].granularity |= (ring & 0xF0);
    gdt[index].access 		= type;
}
