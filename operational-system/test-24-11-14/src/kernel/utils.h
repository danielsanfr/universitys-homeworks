//;-------------- INTERFACE DE FUNÇÕES ÚTEIS PARA TRATAMENTO DE STRINGS E DA MEMÓRIA ----------------;

void outb(unsigned short port, unsigned char value);
unsigned char inportb(unsigned short port);
unsigned short inw(unsigned short port);
void memcpy(unsigned char *dest, const unsigned char *src, unsigned int len);
void memset(unsigned char *dest, unsigned char val, unsigned int len);
int strcmp(char *str1, char *str2);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);

