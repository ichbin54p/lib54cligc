#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <lib54cligc/lib54cligc.h>
#include <lib54cligc/lib54cligc-widgets.h>

struct lib54cligc_widget_input input = {0, 0, {255, 255, 255}, {50, 50, 40}, {0, 0, 0}, {255, 255, 255}, 11, 0};

char text[11];

void onclick(void){
    strcpy(text, input.content);
}

int main(){
    if (lib54cligc_init() != 0){
        return -1;
    }

    int run = 1;
    int active = 0;
    int cursor = 0;
    int pactive = 0;

    char lk = 0;

    struct lib54cligc_widget_button submit = {1, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}, onclick};

    lib54cligc_widget_input_create("type...", &input);

    while (run){
        if (active == 1){
            active = 0;
        }

        char key = 0;
        size_t kl = read(STDIN_FILENO, &key, 1);

        if (key != lk){
            if (kl > 0){
                switch (key){
                    case 'q':
                        run = 0;
                        break;
                    case '\n':
                        active = 1;
                        break;
                    case 'a':
                        if (!pactive){
                            cursor -= 1;
                        }
                        break;
                    case 'd':
                        if (!pactive){
                            cursor += 1;
                        }
                        break;
                }
            }

            lk = key;
        }

        lib54cligc_pixel_text(1, 5, text, 255, 255, 255, 0, 0, 0);

        lib54cligc_widget_input_display(1, 10, cursor, active, key, &pactive, &input);
        lib54cligc_widget_button_display(16, 10, "submit", cursor, active, submit);

        fflush(stdout);
        usleep(30000);
        lib54cligc_pixel_clear();
    }

    lib54cligc_widget_input_destroy(&input);
    lib54cligc_quit();
}