global switchToRealMode
switchToRealMode:
cli
mov eax, cr0 ; load cr0
and al, not 1 ; set cr0 to false
mov cr0, eax
ret