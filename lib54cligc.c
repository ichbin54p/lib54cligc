#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

struct lib54cligc_pixelmap {
    char* x;
    char* y;
    int idx;
};

struct termios TERMINAL_FLAGS;
struct termios TERMINAL_FLAGS_NEW;
struct winsize TERMINAL_SIZE;
struct lib54cligc_pixelmap lib54cligc_pixels;

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

    if (tcsetattr(STDIN_FILENO, TCSANOW, &TERMINAL_FLAGS_NEW) == -1){
        printf("init: tcsetattr error\n");
        return -1;
    }

    int pms = TERMINAL_SIZE.ws_col * TERMINAL_SIZE.ws_row;

    printf("Allocating %d bytes for pm\n", pms * 2);
    fflush(stdout);
    sleep(1);

    lib54cligc_pixels.x = malloc(pms);
    lib54cligc_pixels.y = malloc(pms);
    lib54cligc_pixels.idx = 0;

    printf("\033[?25l");

    for (int i = 0; i < TERMINAL_SIZE.ws_row - 1; i++){
        printf("\n");
    }

    printf("\n\033[%dA", TERMINAL_SIZE.ws_row);
    fflush(stdout);

    if (lib54cligc_pixels.x == NULL || lib54cligc_pixels.y == NULL){
        printf("init: allocating memory error\n");
        return -1;
    }

    return 0;
}

void lib54cligc_pixel_add(int x, int y, int r, int g, int b){
    printf("\033[%d;%dH\033[48;2;%d;%d;%dm  \033[0m", y, (x * 2) - 1, r, g, b);
    fflush(stdout);

    lib54cligc_pixels.x[lib54cligc_pixels.idx] = x + 1;
    lib54cligc_pixels.y[lib54cligc_pixels.idx] = y + 1;
    lib54cligc_pixels.idx += 1;
}

void lib54cligc_pixel_add_advanced(int x, int y, char* e){
    printf("\033[%d;%dH%s", y, (x * 2) - 1, e);
    // printf("\n\n\n%d: %d", x, y);
    fflush(stdout);
}

void lib54cligc_pixel_remove_fast(int i){
    int x = lib54cligc_pixels.x[i];
    int y = lib54cligc_pixels.y[i];

    lib54cligc_pixel_add_advanced(x - 1, y - 1, "\033[0m  ");

    lib54cligc_pixels.x[i] = 0;
    lib54cligc_pixels.y[i] = 0;
}

void lib54cligc_pixel_remove(int x, int y){
    printf("\033[0m\033[%d;%dH  ", y, (x * 2) - 1);
    fflush(stdout);

    for (int i = 0; i < TERMINAL_SIZE.ws_col * TERMINAL_SIZE.ws_row; i++){
        if (lib54cligc_pixels.x[i] == x || lib54cligc_pixels.y[i] == y){
            lib54cligc_pixels.x[i] = 0;
            lib54cligc_pixels.y[i] = 0;
            break;
        }
    }
}

void lib54cligc_pixel_clear(){
    for (int i = 0; i < TERMINAL_SIZE.ws_col * TERMINAL_SIZE.ws_row; i++){
        if (lib54cligc_pixels.x[i] > 0 || lib54cligc_pixels.y[i] > 0){
            lib54cligc_pixel_remove_fast(i);
        }
    }

    lib54cligc_pixels.idx = 0;

    printf("\033[;H");
    fflush(stdout);
}

int lib54cligc_quit(){
    if (tcsetattr(STDIN_FILENO, TCSANOW, &TERMINAL_FLAGS) == -1){
        printf("quit: tcsetattr error\n");
        return -1;
    }

    lib54cligc_pixel_clear();

    free(lib54cligc_pixels.x);
    free(lib54cligc_pixels.y);

    printf("\033[?25h");
    printf("quit: successful\n");

    return 0;
}