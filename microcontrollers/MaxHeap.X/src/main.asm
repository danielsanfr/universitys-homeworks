#include "p16f628a.inc"

; CONFIG
; __config 0xFF19
 __CONFIG _FOSC_INTOSCCLK & _WDTE_OFF & _PWRTE_OFF & _MCLRE_OFF & _BOREN_OFF & _LVP_OFF & _CPD_OFF & _CP_OFF

count		EQU		h'20'

			ORG		0x0000
			GOTO	setup

			ORG		0x0004
			RETFIE

setup:

loop:
			GOTO	loop

			ORG		0x2100
			DE	    0x0B, "Hello World"

			END