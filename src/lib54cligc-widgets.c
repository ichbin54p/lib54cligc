#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib54cligc.h"

typedef struct {
    int index;
    int fg1[3];
    int bg1[3];
    int fg2[3];
    int bg2[3];
    void (*onclick)(void);
} lib54cligc_widget_button;

typedef struct {
    int active;
    int index;
    int fg1[3];
    int bg1[3];
    int fg2[3];
    int bg2[3];
    int max_chars;
    int chars;
    char* content;
    char* placeholder;
} lib54cligc_widget_input;

int lib54cligc_widget_input_create(char* placeholder, lib54cligc_widget_input* input){
    FILE* f = fopen("log", "a");

    input->content = malloc(input->max_chars + 1);
    input->placeholder = malloc(input->max_chars + 1);

    if (strlen(placeholder) > input->max_chars){
        fprintf(f, "exec: Widget: unable to create input %d, placeholder length exceeds max length %d > %d\n", input->index, strlen(placeholder), input->max_chars);
        fclose(f);

        return -1;
    }

    for (int i = 0; i < input->max_chars; i++){
        input->content[i] = ' ';

        if (i < strlen(placeholder)){
            input->placeholder[i] = placeholder[i];
        } else {
            input->placeholder[i] = ' ';
        }
    }

    input->content[input->max_chars] = '\0';
    input->placeholder[input->max_chars] = '\0';

    fprintf(f, "exec: Widget: created input %d:\n- content_size: %d bytes\n- placeholder_size: %d bytes\n", input->index, input->max_chars + 1, strlen(placeholder) + 1);
    fclose(f);

    return 0;
}

int lib54cligc_widget_input_destroy(lib54cligc_widget_input* input){
    FILE* f = fopen("log", "a");

    free(input->content);
    free(input->placeholder);

    fprintf(f, "exec: Widget: destroyed input %d\n", input->index);
    fclose(f);

    return 0;
}

void lib54cligc_widget_input_display(int x, int y, int index, int active, char k, int* pactive, lib54cligc_widget_input* input){
    FILE* f = fopen("dlog", "a");
    char* o;

    if (input->chars < 1){
        o = input->placeholder;
    } else {
        o = input->content;
    }

    if (input->active){
        if (k > 0){
            if (k == 127){
                if (input->chars > 0){
                    input->chars -= 1;
                    input->content[input->chars] = ' ';
                } else {
                    fprintf(f, "Widget: input %d: there are no characters to remove\n", input->index);
                }
            } else if (k == '\x1b' || k == '\n'){
                *pactive = 0;
                input->active = 0;

                fprintf(f, "Widget: input %d: inactive\n", input->index);
            } else if (k == '\t'){
                fprintf(f, "Widget: input %d: illegal key was pressed\n", input->index);
            } else {
                if (input->chars < input->max_chars - 1){
                    input->content[input->chars] = k;
                    input->chars += 1;
                } else {
                    fprintf(f, "Widget: input %d: unable to input character %c, content length max\n", input->index, k);
                }
            }
        }
        
        lib54cligc_pixel_text(x, y, o, input->fg2[0], input->fg2[1], input->fg2[2], input->bg2[0], input->bg2[1], input->bg2[2]);
    } else {
        if (index == input->index){
            if (k > 0){
                if (k == '\n'){
                    *pactive =  1;
                    input->active = 1;

                    fprintf(f, "Widget: input %d: active\n", input->index);
                } else {
                    fprintf(f, "Widget: input %d: unable to input character %c, not active %d\n", input->index, k, k);
                }
            }

            lib54cligc_pixel_text(x, y, o, input->fg2[0], input->fg2[1], input->fg2[2], input->bg2[0], input->bg2[1], input->bg2[2]);
        } else {
            lib54cligc_pixel_text(x, y, o, input->fg1[0], input->fg1[1], input->fg1[2], input->bg1[0], input->bg1[1], input->bg1[2]);
        }
    }

    fclose(f);
}

void lib54cligc_widget_button_display(int x, int y, char* label, int index, int activate, lib54cligc_widget_button button){
    if (index == button.index){
        lib54cligc_pixel_text(x, y, label, button.fg2[0], button.fg2[1], button.fg2[2], button.bg2[0], button.bg2[1], button.bg2[2]);

        if (activate){
            FILE* f = fopen("dlog", "a");

            if (!button.onclick){
                fprintf(f, "Widget: error: button %d: onclick\n", button.index);
                fclose(f);
            } else {
                fprintf(f, "Widget: button %d: onclick: executing onclick\n", button.index);
                fclose(f);
                button.onclick();
            }
        }
    } else {
        lib54cligc_pixel_text(x, y, label, button.fg1[0], button.fg1[1], button.fg1[2], button.bg1[0], button.bg1[1], button.bg1[2]);

        if (activate){
            FILE* f = fopen("dlog", "a");

            fprintf(f, "Widget: button %d: onclick: not executing onclick (i: %d)\n", button.index, index);
            fclose(f);
        }
    }
}