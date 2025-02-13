#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

struct termios TERMINAL_FLAGS;
struct termios TERMINAL_FLAGS_NEW;
struct winsize TERMINAL_SIZE;

int lib54cligc_init(){
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &TERMINAL_SIZE) == -1){
        printf("init: ioctl error\n");
        return -1;
    }

    if (tcgetattr(STDIN_FILENO, &TERMINAL_FLAGS) == -1){
        printf("init: tcgetattr error\n");
        return -1;
    }

    TERMINAL_FLAGS_NEW = TERMINAL_FLAGS;
    TERMINAL_FLAGS_NEW.c_lflag &= ~(ICANON | ECHO);
    TERMINAL_FLAGS_NEW.c_oflag &= -ONLCR;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &TERMINAL_FLAGS_NEW) == -1){
        printf("init: tcsetattr error\n");
        return -1;
    }

    printf("\033[?25l");

    for (int i = 0; i < TERMINAL_SIZE.ws_row - 1; i++){
        printf("\n");
    }

    printf("\n\033[%dA", TERMINAL_SIZE.ws_row);
    fflush(stdout);

    return 0;
}

int lib54cligc_quit(){
    if (tcsetattr(STDIN_FILENO, TCSANOW, &TERMINAL_FLAGS) == -1){
        printf("quit: tcsetattr error\n");
        return -1;
    }

    printf("\033[?25h");
    printf("quit: successful\n");

    return 0;
}

void lib54cligc_pixel_add(int x, int y, int r, int g, int b){
    printf("\033[%dB\033[%dC\033[48;2;%d;%d;%dm  \033[0m\033[%dA\033[%dD", y, x + 1, r, g, b, y, x + 2);
    fflush(stdout);
}