; archivo: modo_protegido.asm
; Compilar: nasm -f bin -o modo_protegido.bin modo_protegido.asm
[org 0x7C00]         ; Dirección estándar de carga de un bootloader

start:
    cli             ; Desactiva interrupciones
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    lgdt [gdt_descriptor]   ; Carga la GDT

    mov eax, cr0
    or eax, 1          ; Activar bit PE (Protection Enable) en CR0
    mov cr0, eax

    jmp 0x08:protected_mode_start ; Salta con selector de segmento de código

; -----------------------------
; Segmento en modo protegido
; -----------------------------
[BITS 32]
protected_mode_start:
    mov ax, 0x10      ; Selector de segmento de datos
    mov ds, ax
    mov es, ax
    mov ss, ax

    ; Intentamos escribir en el segmento de datos
    mov [0x100000], byte 'A'  ; Esta dirección está mapeada al segmento de datos

    jmp $

; -----------------------------
; GDT (Global Descriptor Table)
; -----------------------------
gdt_start:
    dq 0x0000000000000000 ; Null descriptor

    ; Descriptor de código: base=0x00000000, limit=0xFFFFF, type=0x9A (ejecutable)
    dq 0x00CF9A000000FFFF

    ; Descriptor de datos: base=0x00100000, limit=0x0FFFF, tipo=0x92 (lectura/escritura)
    ; CAMBIALO A 0x90 para que sea solo lectura
    dq 0x0000920010000FFF

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

gdt_end:

; Rellenar hasta 512 bytes para que sea un bootloader válido
times 510 - ($ - $$) db 0
dw 0xAA55
