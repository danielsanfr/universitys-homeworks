//;-------------- FUNÇÕES DA GDT DO KERNEL ----------------;

//adicionar segmento para composição na tabela gdt
void gdt_add_seg(int num_segment, unsigned long base, unsigned long limit, 
		unsigned char access, unsigned char granularity);

//inicia a gdt, seta o limite e o tamanho, cria os segmentos e inicializa
void gdt_init(void);

