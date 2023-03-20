global readValues 
global jumpToVals
; HARD DRIVE STUFF
DA_PACK:
  db 0x10 
  db 0
blkcnt:
  dw 6 ; size to be read (reads 16 sectors)
db_add:
  ; memory address for data to be written to
  dw 0x7C00
  dw 0
d_lba:
  dd 1
  dd 0
readValues:
mov si, DA_PACK
mov dl, 0x80 ; Set current hard drive
int 0x13
ret
jumpToVals:
jmp 0x7C00