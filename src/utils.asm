; Global functions for main.c to use (Based)
global switchToRealMode

switchToRealMode:
cli
mov eax, cr0 ; load cr0
mov eax, 0
mov cr0, eax
ret
