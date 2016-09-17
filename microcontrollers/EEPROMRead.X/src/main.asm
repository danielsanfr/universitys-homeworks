#include "p16f628a.inc"

; CONFIG
; __config 0xFF19
 __CONFIG _FOSC_INTOSCCLK & _WDTE_OFF & _PWRTE_OFF & _MCLRE_OFF & _BOREN_OFF & _LVP_OFF & _CPD_OFF & _CP_OFF

total		EQU		h'20'
count		EQU		h'21'

			ORG		0x0000
			GOTO	setup

			ORG		0x0004
			RETFIE

read_ee_byte:
			BANKSEL	EEADR
			MOVWF	EEADR
			BSF		EECON1, RD
			MOVF	EEDATA, W
			BANKSEL	PORTA
			RETURN

read_ee_data:
			MOVLW	h'22'
			MOVWF	FSR
			CLRF	count
read_loop:
			INCF	count
			MOVF	count, W
			CALL	read_ee_byte
			MOVWF	INDF
			INCF	FSR
			MOVF	count, W
			SUBWF	total, W
			BTFSS	STATUS, Z
			GOTO	read_loop
			RETURN

setup:
			BANKSEL	PORTA
			MOVLW	h'20'
			MOVWF	FSR
			MOVLW	00
			CALL	read_ee_byte
			MOVWF	INDF
			CALL	read_ee_data

loop:
			GOTO	loop

			ORG		0x2100
			DE	    0x0B, "Hello World"

			END