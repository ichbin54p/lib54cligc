#include <stdio.h>
#include "lib54cligc.h"

struct lib54cligc_widget_button {
    int index;
    int fg1[3];
    int bg1[3];
    int fg2[3];
    int bg2[3];
    void (*onclick)(void);
};

void lib54cligc_widget_button_display(int x, int y, char* label, int index, int activate, struct lib54cligc_widget_button button){
    if (index == button.index){
        lib54cligc_pixel_text(x, y, label, button.fg2[0], button.fg2[1], button.fg2[2], button.bg2[0], button.bg2[1], button.bg2[2]);

        if (activate){
            FILE* f = fopen("dlog", "a");

            if (!button.onclick){
                fprintf(f, "Widget: error: button: onclick, button: %d\n", button.index);
                fclose(f);
            } else {
                fprintf(f, "Widget: button: onclick: executing onclick for button: %d\n", button.index);
                fclose(f);
                button.onclick();
            }
        }
    } else {
        lib54cligc_pixel_text(x, y, label, button.fg1[0], button.fg1[1], button.fg1[2], button.bg1[0], button.bg1[1], button.bg1[2]);

        if (activate){
            FILE* f = fopen("dlog", "a");

            fprintf(f, "Widget: button: onclick: not executing onclick for button: %d (i: %d)\n", button.index, index);
            fclose(f);
        }
    }
}