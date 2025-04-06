#ifndef LIB54CLIGC_WIDGEHTS_H
#define LIB54CLIGC_WIDGEHTS_H

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

int lib54cligc_widget_input_create(char* placeholder, lib54cligc_widget_input* input);
int lib54cligc_widget_input_destroy(lib54cligc_widget_input* input);
void lib54cligc_widget_input_display(int x, int y, int index, int active, char k, int* pactive, lib54cligc_widget_input* input);
void lib54cligc_widget_button_display(int x, int y, char* label, int index, int activate, lib54cligc_widget_button button);

#endif