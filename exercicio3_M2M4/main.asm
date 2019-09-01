;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------

			mov			#vetor1, R5			; R6 recebe mult2, R7 recebe mult4
			call		#M2M4
			jmp			$
			nop

M2M4:
			mov.b	0(R5), R8				; R8 = tamanho do vetor
			add		#1, R5
			clr		R14
			clr		R6
			clr		R7

loop_divisores:

			mov.b	0(R5), R13
			mov		#0x0002, R12
			call	#udiv
			cmp		#1, R4
			jeq		aumenta_divisiveis_2

dividir_por_4:

			clr		R4
			mov		#0x0004, R12
			call	#udiv
			cmp		#1, R4
			jeq		aumenta_divisiveis_4

proximo_passo_divisao:

			clr		R4
			add		#1, R5
			add		#1, R14

			cmp		R8, R14
			jeq		fim_algoritmo
			jl		loop_divisores

aumenta_divisiveis_2:
			inc		R6
			jmp		dividir_por_4

aumenta_divisiveis_4:
			inc		R7
			jmp		proximo_passo_divisao
                                            
udiv:

			push	R13					; quociente
			push	R14
			clr		R14
			cmp		R12, R13
			jl		fim_divisao

udiv_loop:

			inc		R14
			sub		R12, R13

			cmp		#0, R13
			jeq		divisivel
			cmp		R12, R13
			jeq		udiv_loop
			jhs		udiv_loop
			jl		nao_divisivel

divisivel:
			mov		#1, R4
			jmp		fim_divisao

nao_divisivel:

			mov		#0, R4
			jmp		fim_divisao

fim_divisao:

			pop		R14
			pop		R13
			ret

fim_algoritmo:

			ret


			.data

vetor1	 	.byte		6, 12, 4, 2, 6, 10, 8
;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
