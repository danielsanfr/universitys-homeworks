//;-------------- FUNÇÕES DA IDT ----------------;

//adicionar base para composição na tabela idt
void idt_add_exc(int num_exception, unsigned long base, unsigned short selector,
					unsigned char flags);

//inicia a idt
void idt_init(void);

