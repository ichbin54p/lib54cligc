#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <lib54cligc/lib54cligc.h>

long long t() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
}

int main(){
    long long tnow;
    long long tsec;

    char sfps[4];

    int fps = 0;
    int ifps = 0;
    int x = 0;
    int y = 0;
    int vx = 1;
    int vy = 1;
    
    lib54cligc_init();

    while (1){
        tsec = t();

        if ((tsec - tnow) / 1000 > 1){
            tnow = t();
            fps = ifps;
            ifps = 0;

            sprintf(sfps, "%d", fps);
        } else {
            ifps += 1;
        }

        char key;
        ssize_t kl = read(STDIN_FILENO, &key, 1);

        if (kl > 0){
            if (key == 'q'){
                break;
            }
        }

        if (x < 1){
            vx = 1;
        } else if (x >= TERMINAL_SIZE.ws_col / 2) {
            vx = -1;
        } if (y < 1){
            vy = 1;
        } else if (y >= TERMINAL_SIZE.ws_row){
            vy = -1;
        }

        x += vx;
        y += vy;

        lib54cligc_pixel_add(x, y, 255, 25, 25);
        lib54cligc_pixel_text(1, 1, sfps, 255, 255, 255, 0, 0, 0);
        lib54cligc_pixel_text(5, 1, "FPS", 255, 255, 255, 0, 0, 0);
        fflush(stdout);

        usleep(15000);
        lib54cligc_pixel_clear();
    }

    lib54cligc_quit();

    return 0;
}
