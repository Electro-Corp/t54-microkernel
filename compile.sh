cd out
ls
rm *
ls
cd ..
nasm -f elf src/boot.asm -o out/boot.o
nasm -f elf src/utils.asm -o out/util.o
nasm -f elf src/hd.asm -o out/hd.o
echo Compiling C Source
# Compile C Source/
gcc -c src/main.c -m32 -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W -o out/main.o
# for the HD
gcc -c src/goof.c -m32 -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W -o out/goof.o

echo Linking
ld -T src/link.ld -melf_i386 out/main.o -Ttext 0x0 out/hd.o out/boot.o out/util.o -o boot/kernel
ld -T src/link.ld -melf_i386 out/goof.o -Ttext 0x0 out/hd.o out/boot.o out/util.o -o test.img
echo Creating ISO
#mkisofs -R                                   \
#                -b grub/stage2_eltorito    \
#                -no-emul-boot                   \
#                -boot-load-size 4               \
#                -A T54                           \
 #               -input-charset utf8             \
  #              -quiet                          \
   #             -boot-info-table                \
    #            -o t54.iso                       \
     #           boot
#qemu-system-x86_64 -cdrom t54.iso
qemu-system-x86_64 -kernel boot/kernel -machine type=pc-i440fx-3.1 -hdd test.img