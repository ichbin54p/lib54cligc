#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>

typedef struct {
    int* x;
    int* y;
    int idx;
} lib54cligc_pixelmap;

struct termios TERMINAL_FLAGS;
struct termios TERMINAL_FLAGS_NEW;
struct winsize TERMINAL_SIZE;

lib54cligc_pixelmap lib54cligc_pixels;
lib54cligc_pixelmap lib54cligc_text;

int pms;
int tms;

void lr(){
    FILE* log = fopen("log", "w");
    FILE* dlog = fopen("dlog", "w");

    fprintf(log, "--- lib54cligc log ---\n\n");
    fprintf(dlog, "--- lib54cligc detailed log ---\n\n");

    fclose(log);
    fclose(dlog);
}

int lib54cligc_init(){
    lr();

    FILE* log = fopen("log", "a");

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &TERMINAL_SIZE) == -1){
        fprintf(log, "init: ioctl error\n");
        return -1;
    } else {
        fprintf(log, "init: terminal size:\n- colums: %d\n- lines: %d\n", TERMINAL_SIZE.ws_col, TERMINAL_SIZE.ws_row);
    }

    if (tcgetattr(STDIN_FILENO, &TERMINAL_FLAGS) == -1){
        fprintf(log, "init: tcgetattr error\n");
        return -1;
    } else {
        fprintf(log, "init: copied terminal flags\n");
    }

    TERMINAL_FLAGS_NEW = TERMINAL_FLAGS;
    TERMINAL_FLAGS_NEW.c_lflag &= ~(ICANON | ECHO | ISIG);

    if (tcsetattr(STDIN_FILENO, TCSANOW, &TERMINAL_FLAGS_NEW) == -1){
        fprintf(log, "init: tcsetattr error\n");
        return -1;
    } else {
        fprintf(log, "init: set terminal flags:\n- c:%d\n- i:%d\n", TERMINAL_FLAGS_NEW.c_cflag, TERMINAL_FLAGS_NEW.c_iflag);
    }

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    pms = (TERMINAL_SIZE.ws_col / 2) * TERMINAL_SIZE.ws_row * sizeof(int);
    tms = TERMINAL_SIZE.ws_col * TERMINAL_SIZE.ws_row * sizeof(int);

    lib54cligc_pixels.x = malloc(pms);
    lib54cligc_pixels.y = malloc(pms);
    lib54cligc_pixels.idx = 0;

    lib54cligc_text.x = malloc(tms);
    lib54cligc_text.y = malloc(tms);
    lib54cligc_text.idx = 0;

    if (!lib54cligc_pixels.x || !lib54cligc_pixels.y || !lib54cligc_text.x || !lib54cligc_text.y){
        fprintf(log, "init: allocating memory error\n");
        return -1;
    } else {
        fprintf(log, "init: allocated memory successfuly\n");
    }

    printf("\033[?25l");

    for (int i = 0; i < TERMINAL_SIZE.ws_row - 1; i++){
        printf("\n");
    }

    printf("\n\033[%dA", TERMINAL_SIZE.ws_row);
    fflush(stdout);

    fprintf(log, "init: allocating %d bytes for pms, %d bytes for tms\n", pms, tms);
    fclose(log);

    return 0;
}

void lib54cligc_pixel_add(int x, int y, int r, int g, int b){
    if (x > 0 && x < (TERMINAL_SIZE.ws_col / 2) + 1 && y > 0 && y < TERMINAL_SIZE.ws_row + 1){
        printf("\033[%d;%dH\033[48;2;%d;%d;%dm  \033[0m", y, (x * 2) - 1, r, g, b);

        lib54cligc_pixels.x[lib54cligc_pixels.idx] = x + 1;
        lib54cligc_pixels.y[lib54cligc_pixels.idx] = y + 1;
        lib54cligc_pixels.idx += 1;
    }
}

void lib54cligc_pixel_text(int x, int y, char* text, int fr, int fg, int fb, int br, int bg, int bb){
    if (x > 0 && x < (TERMINAL_SIZE.ws_col - strlen(text)) + 1 && y > 0 && y < TERMINAL_SIZE.ws_row + 1){
        printf("\033[%d;%dH\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm%s\033[0m", y, x, fr, fg, fb, br, bg, bb, text);

        for (int i = 0; i < strlen(text); i++){
            lib54cligc_text.x[lib54cligc_text.idx] = x + i + 1;
            lib54cligc_text.y[lib54cligc_text.idx] = y + 1;
            lib54cligc_text.idx += 1;
        }
    }
}

void lib54cligc_pixel_text_advanced(int x, int y, char* text){
    if (x > 0 && x < (TERMINAL_SIZE.ws_col - strlen(text)) + 1 && y > 0 && y < TERMINAL_SIZE.ws_row + 1){
        printf("\033[%d;%dH%s", y, x, text);
    }
}

void lib54cligc_pixel_add_advanced(int x, int y, char* e){
    if (x > 0 && x < (TERMINAL_SIZE.ws_col / 2) + 1 && y > 0 && y < TERMINAL_SIZE.ws_row + 1){
        printf("\033[%d;%dH%s", y, (x * 2) - 1, e);
    }
}

void lib54cligc_pixel_rect(int x, int y, int w, int h, int r, int g, int b){
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            lib54cligc_pixel_add(j + x, i + y, r, g, b);
        }
    }
}

void lib54cligc_pixel_remove_fast(int i){
    int x = lib54cligc_pixels.x[i];
    int y = lib54cligc_pixels.y[i];

    lib54cligc_pixel_add_advanced(x - 1, y - 1, "\033[0m  ");

    lib54cligc_pixels.x[i] = 0;
    lib54cligc_pixels.y[i] = 0;
}

void lib54cligc_text_remove_fast(int i){
    int x = lib54cligc_text.x[i];
    int y = lib54cligc_text.y[i];

    lib54cligc_pixel_text_advanced(x - 1, y - 1, "\033[0m ");

    lib54cligc_text.x[i] = 0;
    lib54cligc_text.y[i] = 0;
}

void lib54cligc_pixel_remove(int x, int y){
    printf("\033[0m\033[%d;%dH  ", y, (x * 2) - 1);

    for (int i = 0; i < TERMINAL_SIZE.ws_col * TERMINAL_SIZE.ws_row; i++){
        if (lib54cligc_pixels.x[i] == x || lib54cligc_pixels.y[i] == y){
            lib54cligc_pixels.x[i] = 0;
            lib54cligc_pixels.y[i] = 0;
            break;
        }
    }
}

void lib54cligc_text_remove(int x, int y){
    printf("\033[0m\033[%d;%dH  ", y, x);

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
        if (lib54cligc_text.x[i] > 0 || lib54cligc_text.y[i] > 0){
            lib54cligc_text_remove_fast(i);
        }
        if (i < (TERMINAL_SIZE.ws_col / 2) * TERMINAL_SIZE.ws_row){
            if (lib54cligc_pixels.x[i] > 0 || lib54cligc_pixels.y[i] > 0){
                lib54cligc_pixel_remove_fast(i);
            }
        }
    }

    lib54cligc_pixels.idx = 0;
    lib54cligc_text.idx = 0;

    printf("\033[;H");
    fflush(stdout);
}

int lib54cligc_quit(){
    FILE* log = fopen("log", "a");

    if (tcsetattr(STDIN_FILENO, TCSANOW, &TERMINAL_FLAGS) == -1){
        fprintf(log, "quit: tcsetattr error\n");
        return -1;
    } else {
        fprintf(log, "quit: tcsetattr success\n");
    }

    lib54cligc_pixel_clear();
    printf("\033[?25h");

    fprintf(log, "quit: freeing memory\n");

    free(lib54cligc_pixels.x);
    fprintf(log, "quit: freed lib54cligc_pixels.x\n");

    free(lib54cligc_pixels.y);
    fprintf(log, "quit: freed lib54cligc_pixels.y\n");

    free(lib54cligc_text.x);
    fprintf(log, "quit: freed lib54cligc_text.x\n");

    free(lib54cligc_text.y);
    fprintf(log, "quit: freed lib54cligc_text.y\n");

    fprintf(log, "quit: successful\n");
    fclose(log);

    return 0;
}