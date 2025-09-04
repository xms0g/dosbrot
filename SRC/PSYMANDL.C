#include "vga.h"
#include "keybrd.h"
#include "io.h"

#define WIDTH 320
#define HEIGHT 200

#define DAC_INDEX 0x3C8
#define DAC_DATA  0x3C9

int computeMandelbrot(double re, double im, int iteration);
void initPalette(unsigned char* palette);
void setPalette(unsigned char* palette);
void cyclePalette(unsigned char* palette, int t);

void main(void) {
    int x, y, value;
	unsigned char palette[768];
	int t = 0;
	
    const double remin = -2.0;
    const double remax = 1.0;
    const double immin = -1.0;
    const double immax = 1.0;
	
	const double dx = (remax - remin)/(WIDTH - 1);
	const double dy = (immax - immin)/(HEIGHT - 1);
    
    _setMode(VGA_MODE_13H);
	kbInit();
	
	initPalette(palette);
	setPalette(palette);
	
	for (y = 0; y < HEIGHT; y++) {
		double im = immax - y * dy;

		for (x = 0; x < WIDTH; x++) {
			value = computeMandelbrot(remin + x * dx, im, 255);
			_putpixel(x, y, 255 - value % 256);
		}	
	}

	while(1) {
		if (kbHit(ESC)) break;

		_waitvretrace();
		_waitvretrace();
		
		cyclePalette(palette, t++);
	}

	_setMode(VGA_MODE_3H);
	kbExit();
}

int computeMandelbrot(double re, double im, int iteration) {
   	double zR = re;
    double zI = im;
	
	int i;
	for (i = 0; i < iteration; ++i) {
	    double r2 = zR * zR;
	    double i2 = zI * zI;
		
		if (r2 + i2 > 4.0) {
			return i;
		}
        
		zI = 2.0 * zR * zI + im;
		zR = r2 - i2 + re;
	}
    
	return iteration;
}

void initPalette(unsigned char* palette) {
	signed char r = 0, g = 0, b = 0;
	int dr = 1, dg = 3, db = 2;
	
	int i;
	for (i = 0; i < 256; ++i) {
		palette[i * 3 + 0] = (unsigned char)r;
		palette[i * 3 + 1] = (unsigned char)g;
		palette[i * 3 + 2] = (unsigned char)b;
		
		if (r + dr > 63 || r + dr < 0) {
			dr = -dr;
		}
		if(g + dg > 63 || g + dg < 0) {
			dg = -dg;
		}
		if(b + db > 63 || b + db < 0) {
			db = -db;
		}
		r += dr; 
		g += dg; 
		b += db;
	}
}

void setPalette(unsigned char* palette) {
	int i;

	_outp(DAC_INDEX, 0);
  	for (i = 0; i < 768; ++i) {
		_outp(DAC_DATA, palette[i]);
	}
}

void cyclePalette(unsigned char* palette, int t) {
  	int i;

	_outp(DAC_INDEX, 0);
  	for (i = 0; i < 768; ++i) {
		_outp(DAC_DATA, palette[(i + t*3) % 768]);
	}
}
