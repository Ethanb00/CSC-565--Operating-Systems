dd if=/dev/zero of=mynewfloppy.img bs=512 count=2880
nasm bootload.asm
dd if=bootload of=mynewfloppy.img bs=512 conv=notrunc
bcc -ansi -c -o kernel_c_part.o kernel.c
as86 kernel.asm -o kernel_asm_part.o
ld86 -o kernel kernel_c_part.o kernel_asm_part.o
dd if=kernel of=mynewfloppy.img bs=512 conv=notrunc seek=3
java -jar simulator.jar mynewfloppy.img
