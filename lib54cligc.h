#ifndef LIB54CLIGC_H
#define LIB54CLIGC_H

struct lib54cligc_pixelmap {
    char* x;
    char* y;
    int idx;
};

extern struct termios TERMINAL_FLAGS;
extern struct termios TERMINAL_FLAGS_NEW;
extern struct winsize TERMINAL_SIZE;
extern struct lib54cligc_pixelmap lib54cligc_pixels;

int lib54cligc_init();
void lib54cligc_pixel_add(int x, int y, int r, int g, int b);
void lib54cligc_pixel_add_advanced(int x, int y, char* e);
void lib54cligc_pixel_remove_fast(int i);
void lib54cligc_pixel_remove(int x, int y);
void lib54cligc_pixel_clear();
int lib54cligc_quit();

#endif