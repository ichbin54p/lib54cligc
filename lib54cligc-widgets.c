#include <stdio.h>
#include "lib54cligc.h"

struct lib54cligc_widget_button {
    int index;
    void* onclick;
};

void lib54cligc_widget_button_display(int x, int y, char* label)