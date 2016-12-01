#include "p16f688.inc"

; CONFIG
; __config 0xF0D5
 __CONFIG _FOSC_INTOSCCLK & _WDTE_OFF & _PWRTE_OFF & _MCLRE_OFF & _CP_OFF & _CPD_OFF & _BOREN_OFF & _IESO_OFF & _FCMEN_OFF

#define		ON			1
#define		OFF			0
#define		INPUT		1
#define		OUTPUT		0

max_time	EQU			D'10'

			ORG			0x0000			; Processor reset vector
			GOTO		setup			; Go to beginning of program

			ORG			0x0004			; Interrupt vector
			INCF		PORTA
			BCF			INTCON,T0IF
			MOVLW		max_time
			MOVWF		TMR0
			RETFIE

setup:
			BANKSEL		TRISA

			; =================== Configure PORTA as output ====================
			MOVLW		0x00
			MOVWF		TRISA

			; ================== Configure TMR0 and Prescaler ==================
			BANKSEL		OPTION_REG
			MOVLW		B'11010011'
			MOVWF		OPTION_REG
			MOVLW		B'01100101'		; Configure internal clock to 4MHz
			MOVWF		OSCCON

			; ====================== Enable interruptions ======================
			MOVLW		B'10100000'
			MOVWF		INTCON

			BANKSEL		PORTA

			; =================== Set value to TMR0 overflow ===================
			MOVLW		max_time
			MOVWF		TMR0

loop:
			GOTO		loop			; Loop forever

			END