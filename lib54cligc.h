#ifndef LIB54CLIGC_H
#define LIB54CLIGC_H

extern struct termios TERMINAL_FLAGS;
extern struct termios TERMINAL_FLAGS_NEW;
extern struct winsize TERMINAL_SIZE;

int lib54cligc_init();
int lib54cligc_quit();
void lib54cligc_pixel_add(int x, int y, int r, int g, int b);

#endif