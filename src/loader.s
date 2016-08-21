global loader   ;entry symbol for elf
MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -MAGIC_NUMBER
KERNEL_STACK_SIZE equ 4096


%include "stdio.inc"

section .bss
	align 4
kernel_stack:
	resb KERNEL_STACK_SIZE

section .text
	align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM
	
section .data
	msg : db  0x0A, 0x0A, 0x0A, "               <[ OS Development Series Tutorial 10 ]>"
    	db  0x0A, 0x0A,             "           Basic 32 bit graphics demo in Assembly Language", 0


loader:
	mov eax,0xBADDEED
	mov esp,kernel_stack+KERNEL_STACK_SIZE
	push dword 3
	push dword 2
	push dword 1
	extern sum_of_three
	call sum_of_three

	push word 0x3F8
	extern serial_configure_baud
	call serial_configure_baud

	push word 0x3F8
	extern serial_configure_line
	call serial_configure_line

	push word 0x3F8
	extern serial_configure_buffer
	call serial_configure_buffer

	push word 0x3F8
	extern serial_configure_modem
	call serial_configure_modem

	; Push a char is left to see
	push word 0x3F8
	extern write_serial
	call write_serial

	push word 0x3F8
	extern read_serial
	call read_serial

.loop:
	jmp .loop