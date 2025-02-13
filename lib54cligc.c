#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct termios TERMINAL_FLAGS;
struct termios TERMINAL_FLAGS_NEW;

int lib54cligc_init(){
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

    return 0;
}

int lib54cligc_quit(){
    if (tcsetattr(STDIN_FILENO, TCSANOW, &TERMINAL_FLAGS) == -1){
        printf("quit: tcsetattr error\n");
        return -1;
    }

    printf("quit: successful\n");

    return 0;
}