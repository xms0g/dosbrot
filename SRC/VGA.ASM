.model small
.data
PALETTE_INDEX equ 03C8h
PALETTE_DATA  equ 03C9h
.code
public __waitvretrace
public __putpixel
public __setMode
public __setPalette
; -------------------------------------------------------------
; void _Cdecl _waitvretrace(void)                             ;
; -------------------------------------------------------------
__waitvretrace proc
    cli
    ;If vert. retrace bit is set, wait for it to clear
v1: 
    mov dx, 03dah  ;dx <- VGA status register
    in al, dx      ;al <- status byte
    test al, 08h   ;is bit 3 (vertical retrace bit) set
    jnz v1         ;If so, wait for it to clear
    
    ;When it's cleared, wait for it to be set
v2: 
    mov dx, 03dah
    in al, dx
    test al, 08h
    jz v2           ;loop back till vert. retrace bit is newly set
    sti
    ret
__waitvretrace endp

; -------------------------------------------------------------
; void _Cdecl _putpixel(int x, int y, char color)             ;
; -------------------------------------------------------------
__putpixel proc
    push bp      
    mov bp, sp

    push 0A000h
    pop es
    push di
    xor di, di
    mov di, word ptr [bp+4] ;x
    mov cx, word ptr [bp+6] ;y
    mov ax, cx
    shl ax, 08h             ;y<<8
    add di, ax              ;x+(y<<8)
    mov ax, cx
    shl ax, 06h             ;y<<6
    add di, ax              ;x+(y<<8)+(y<<6)
    xor ax, ax
    mov al, byte ptr [bp+8] ;color
    stosb
    
    pop di
    mov sp, bp
    pop bp
    ret        
__putpixel endp

; -------------------------------------------------------------
; void _Cdecl _setMode(int mode)                             ;
; -------------------------------------------------------------
__setMode proc
    push bp       
    mov bp, sp

    mov al, byte ptr [bp+4]
    xor ah, ah         
    int 10h

    mov sp, bp
    pop bp
    ret      
__setMode endp

; -------------------------------------------------------------
; void _Cdecl _setPalette(unsigned char* palette)             ;
; -------------------------------------------------------------
__setPalette proc
    push bp       
    mov bp, sp
    push si
    push cx
    
    mov si, [bp+4] ; SI = palette pointer (DS:SI)
    
    mov dx, PALETTE_INDEX
    xor al, al
    out dx, al

    mov dx, PALETTE_DATA
    mov cx, 768    ; 256 colors * 3 components (R, G, B)

next:
    lodsb                ; AL = [DS:SI], SI++
    out dx, al           ; write to DAC
    loop next

    pop  cx
    pop  si
    mov sp, bp
    pop bp
    ret      
__setPalette endp
end