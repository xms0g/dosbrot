#include "vga.h"

#define WIDTH 320
#define HEIGHT 200

#define CLAMP(v, lo, hi) (v < lo) ? lo:(v > hi) ? hi:v

static char palette[12] = {
	LIGHTMAGENTA,
	MAGENTA,
	BLUE,
	LIGHTBLUE,
	0x50,
	CYAN,
	LIGHTCYAN,
	0x60,
	YELLOW,
    RED,
    LIGHTRED,
	GREEN
};

int computeMandelbrot(double re, double im, int iteration);

void main(void) {
    int x,y,value;
	
    const double remin = -2.0;
    const double remax = 1.0;
    const double immin = -1.0;
    const double immax = 1.0;
	
	const double dx = (remax - remin)/(WIDTH - 1);
	const double dy = (immax - immin)/(HEIGHT - 1);
    
    _initMode(MODE_VGA_13H);
	
	_waitvretrace();
	
	for (y = 0; y < HEIGHT; y++) {
		double im = immax - y * dy;

		for (x = 0; x < WIDTH; x++) {
			value = computeMandelbrot(remin + x * dx, im, 100);
			
			if (value == 100) 
				_putpixel(x, y, BLACK);
			else {
				value = CLAMP(value, 0, 11);
				_putpixel(x, y, palette[value]);
			}	
		}
	}
}

int computeMandelbrot(double re, double im, int iteration) {
    int i;
    double zR = re;
    double zI = im;

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
