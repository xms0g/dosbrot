#ifndef VGA_H
#define VGA_H

#include <_defs.h>
// VGA GFX Mode
#define VGA_MODE_13H 0x13
// VGA Text Mode
#define VGA__MODE_3H 0x3

void _Cdecl _waitvretrace(void);
void _Cdecl _putpixel(int x, int y, char color);
void _Cdecl _setMode(int mode);
void _Cdecl _setPalette(unsigned char* palette);

#endif