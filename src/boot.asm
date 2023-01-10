global entry
section .mbheader
; Align gets to a location via padding with nops i think
align 0x4
MAGIC equ 0x1BADB002 ; tell bootloader that os is bootable
FLAGS equ 0
SUM equ -MAGIC

section .text
align 4; boot header needs to be aligned tp a 4 byte boundry
dd MAGIC ; define 
;dd equ
dd SUM


CSTACK_SIZE equ 30000 ; Stack for C (epoc)

entry:
mov esp, CSTACK_SIZE ; move stack size to esp register
extern kmain
call kmain


jmp entry

section .bss
align 16
