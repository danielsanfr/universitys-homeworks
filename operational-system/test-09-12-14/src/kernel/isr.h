//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;; Interface de tratamento de Interrupções ;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



//;-------------- BLOCO DE DADOS PARA CAPTURA DE INTERRUPÇÃO ----------------;


typedef struct registers
{
	unsigned int ds;	//data segment
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  //usa o pusha (pega todos os registradores)
	unsigned int int_no, err_code; //número da interrupção e código de erro (caso ocorra) 
	unsigned int eip, cs, eflags, useresp, ss; //processador captura automaticamente

} registers_t;

//para possibilitar os registros das chamadas de interrupções ou IRQs 
typedef void (*isr_t)(registers_t);

//;-------------- HANDLER DE INTERRUPÇÃO (CAPTURA DE INTERRUPÇÃO) ----------------;

//chamada quando uma interrupção for recebida
void isr_handler(registers_t regs);

//;-------------- HANDLER DE REQUEST DE INTERRUPÇÃO COM ATUALIZADOR (IRQ) ----------------;

void irq_handler(registers_t regs);

//atualizando os registros de interrupções
void register_interrupt_handler(unsigned char n, isr_t handler);


