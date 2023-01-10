nasm -f elf32 src/boot.asm -o out/boot.o
echo Compiling C Source
# Compile C Source/
gcc src/main.c -m32 -nostdinc -fno-builtin -fno-stack-protector -nostartfiles  -W -o out/main.o
echo Linking
ld -T src/link.ld -melf_i386 out/main.o out/boot.o 

echo Creating ISO
mkisofs -R                              \
                -b boot/grub/stage2_eltorito    \
                -no-emul-boot                   \
                -boot-load-size 4               \
                -A T54                           \
                -input-charset utf8             \
                -quiet                          \
                -boot-info-table                \
                -o t54.iso                       \
                out/kernel
qemu-system-x86_64 -cdrom t54.iso