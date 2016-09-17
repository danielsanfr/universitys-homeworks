#include "p16f628a.inc"

; CONFIG
; __config 0x3F18
 __CONFIG _FOSC_INTOSCIO & _WDTE_OFF & _PWRTE_OFF & _MCLRE_OFF & _BOREN_OFF & _LVP_OFF & _CPD_OFF & _CP_OFF

			ORG		0x0000
			GOTO	setup
			ORG		0x0004
			RETFIE
setup:
loop:
			GOTO	loop

			ORG		0x2100

			END