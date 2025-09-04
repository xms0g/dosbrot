.model small
.data
.code
public __inp
public __outp
; -------------------------------------------------------------
; int _Cdecl _inp(unsigned int port);                         ;
; -------------------------------------------------------------
__inp proc
    push bp      
    mov bp, sp

    mov dx, word ptr [bp+4]
    in al, dx
    
    mov sp, bp
    pop bp
    ret
__inp endp

; -------------------------------------------------------------
; void _Cdecl _outp(unsigned int port, int value)             ;
; -------------------------------------------------------------
__outp proc
    push bp      
    mov bp, sp

    mov dx, word ptr [bp+4]
    mov ax, word ptr [bp+6]
    out dx, al

    mov sp, bp
    pop bp
    ret       
__outp endp
end