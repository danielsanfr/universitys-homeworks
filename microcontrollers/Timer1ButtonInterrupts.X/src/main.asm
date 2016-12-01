#include "p16f688.inc"

; CONFIG
; __config 0xF0D5
 __CONFIG _FOSC_INTOSCCLK & _WDTE_OFF & _PWRTE_OFF & _MCLRE_OFF & _CP_OFF & _CPD_OFF & _BOREN_OFF & _IESO_OFF & _FCMEN_OFF

#define		ON			1
#define		OFF			0
#define		INPUT		1
#define		OUTPUT		0

max_time	EQU			D'50'

			ORG			0x0000			; Processor reset vector
			GOTO		setup			; Go to beginning of program

			ORG			0x0004			; Interrupt vector
			BTFSC		PIR1,TMR1IF
			CALL		handle_timer1
			BTFSC		INTCON,INTF
			CALL		handle_button
			RETFIE

handle_timer1:
			INCF		PORTC
			BCF			PIR1,TMR1IF
			CALL		set_max_time
			RETURN

handle_button:
			DECF		PORTC
			RETURN

set_max_time:
			; =================== Set value to TMR1 overflow ===================
			MOVLW		max_time
			MOVWF		TMR1L
			MOVLW		max_time
			MOVWF		TMR1H
			RETURN

setup:
			; =================== Configure PORTA as output ====================
			CLRF		PORTA
			CLRF		PORTC
			BANKSEL		TRISA
			MOVLW		0x00
			MOVWF		TRISA
			MOVLW		0x00
			MOVWF		TRISC
			BSF			TRISA,RA2

			; ========================= Configure clock ========================
			BANKSEL		OSCCON
			MOVLW		B'01100101'		; Configure internal clock to 4MHz
			MOVWF		OSCCON

			; ====================== Enable interruptions ======================
			BCF			PIR1,TMR1IF
			MOVLW		B'11010000'		; GIE and PEIE
			MOVWF		INTCON
			MOVLW		B'00000001'		; TMR1IE
			MOVWF		PIE1
			BANKSEL		PORTA
			BSF			T1CON,TMR1ON

			CALL		set_max_time

loop:
			SLEEP
			GOTO		loop			; Loop forever

			END