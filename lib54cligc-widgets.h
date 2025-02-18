#ifndef LIB54CLIGC_WIDGEHTS_H
#define LIB54CLIGC_WIDGEHTS_H

struct lib54cligc_widget_button {
    int index;
    int fg1[3];
    int bg1[3];
    int fg2[3];
    int bg2[3];
    void (*onclick)(void);
};

struct lib54cligc_widget_input {
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
};

int lib54cligc_widget_input_create(char* placeholder, struct lib54cligc_widget_input* input);
int lib54cligc_widget_input_destroy(struct lib54cligc_widget_input* input);
void lib54cligc_widget_input_display(int x, int y, int index, int active, char k, int* pactive, struct lib54cligc_widget_input* input);
void lib54cligc_widget_button_display(int x, int y, char* label, int index, int activate, struct lib54cligc_widget_button button);

#endif