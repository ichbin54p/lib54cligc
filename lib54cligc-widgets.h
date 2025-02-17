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

void lib54cligc_widget_button_display(int x, int y, char* label, int index, int activate, struct lib54cligc_widget_button button);

#endif