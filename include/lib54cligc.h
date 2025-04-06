#ifndef LIB54CLIGC_H
#define LIB54CLIGC_H

typedef struct {
    int* x;
    int* y;
    int idx;
} lib54cligc_pixelmap;

extern struct termios TERMINAL_FLAGS;
extern struct termios TERMINAL_FLAGS_NEW;
extern struct winsize TERMINAL_SIZE;
extern struct lib54cligc_pixelmap lib54cligc_pixels;
extern struct lib54cligc_pixelmap lib54cligc_text;

extern int pms;
extern int tms;

int lib54cligc_init();
void lib54cligc_pixel_add(int x, int y, int r, int g, int b);
void lib54cligc_pixel_add_advanced(int x, int y, char* e);
void lib54cligc_pixel_text_advanced(int x, int y, char* text);
void lib54cligc_pixel_rect(int x, int y, int w, int h, int r, int g, int b);
void lib54cligc_pixel_text(int x, int y, char* text, int fr, int fg, int fb, int br, int bg, int bb);
void lib54cligc_pixel_remove_fast(int i);
void lib54cligc_text_remove_fast(int i);
void lib54cligc_pixel_remove(int x, int y);
void lib54cligc_text_remove(int x, int y);
void lib54cligc_pixel_clear();
int lib54cligc_quit();

#endif