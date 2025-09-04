#ifndef VGA_H
#define VGA_H

#include <_defs.h>
// VGA GFX Mode
#define VGA_MODE_13H 0x13
// VGA Text Mode
#define VGA__MODE_3H  0x3

enum COLORS {
    BLACK,		    /* dark colors */
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,		    /* light colors */
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

#ifdef __cplusplus
extern "C" {
#endif
void _Cdecl _waitvretrace(void);
void _Cdecl _putpixel(int x, int y, char color);
void _Cdecl _setMode(int mode);
#ifdef __cplusplus
}
#endif
#endif