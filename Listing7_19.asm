 .cdecls C,LIST,"msp430.h"

 .text
 .retain
 .retainrefs

RESET
 mov.w #WDTPW|WDTHOLD,WDTCTL
 mov.w #__STACK_END,SP
  
 mov.w #0200h,R5
 mov.w #0001h,R6

Loop1:
 mov.w R6,0(R5)
 incd.w R5
 inc.w R6
 cmp.w #0214h,R5
 jlo Loop1

 mov.w #0000h,R7
 mov.w #0200h,R5

Loop2:
 cmp.w #020Ah,R5
 jlo Less
 sub.w @R5,R7
 jmp Incr

Less:
 add.w @R5,R7
Incr:
 incd.w R5
 cmp.w #0214h,R5
 jlo Loop2

 jmp $

;------------------------
;Stack Pointer definition
;------------------------
 .global __STACK_END
 .sect .stack

;-------------------
;Interrupt Vectors
;-------------------
 .sect RESET_VECTOR
 .short RESET
 .end
