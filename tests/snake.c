#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>
#include <sys/time.h>
#include <lib54cligc/lib54cligc.h>

long long tnow;
long long tsec;
long long stime;

enum sd {
    R = 1,
    D = 2,
    L = 3,
    U = 4
};

struct snake {
    short int x;
    short int y;
    char a;
};

struct fruit {
    short int x;
    short int y;
};

struct snake* snake;
struct fruit fruit;

int score = 1;

long long t() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
}

void handle_fruit(){
    if (snake[0].x == fruit.x && snake[0].y == fruit.y){
        while (1){
            int x = rand() % (TERMINAL_SIZE.ws_col / 2) + 1;
            int y = rand() % (TERMINAL_SIZE.ws_row) + 1;
            char s = 1;

            for (int i = 0; i < score; i++){
                if (x == snake[i].x && y == snake[i].y){
                    s = 0;
                    break;
                }
            }

            if (s == 1){
                fruit.x = x;
                fruit.y = y;
                break;
            }
        }

        score += 1;

        snake[score].x = snake[score-1].x;
        snake[score].y = snake[score-1].y;
    }
}

void move_snake(int x, int y, struct snake* snake){
    for (int i = score - 1; i > 0; i--){
        snake[i] = snake[i-1];
    }

    snake[0].x += x;
    snake[0].y += y;
}

int main(){ 
    srand(t() * 1000);

    if (lib54cligc_init() != 0){
        return -1;
    }

    char score_s[4];
    char sfps[4];

    int fps = 0;
    int ifps = 0;
    int run = 1;
    int d = 5;

    snake = malloc(pms * sizeof(struct snake));

    snake[0] = (struct snake) {TERMINAL_SIZE.ws_col / 4, TERMINAL_SIZE.ws_row / 2, 1};
    fruit = (struct fruit) {5 + TERMINAL_SIZE.ws_col / 4, TERMINAL_SIZE.ws_row / 2};

    tnow = t();

    while (run){
        tsec = t();

        if ((tsec - stime) / 50 > 1) {
            stime = t();

            if (d == R) {
                move_snake(1, 0, snake);
            } else if (d == D) {
                move_snake(0, 1, snake);
            } else if (d == L) {
                move_snake(-1, 0, snake);
            } else if (d == U) {
                move_snake(0, -1, snake);
            }

            char key;
            ssize_t kl = read(STDIN_FILENO, &key, 1);

            if (kl > 0){
                if (key == 'q'){
                    run = 0;
                } if (key == 'd' && d != L && d != R) {
                    d = R;
                } else if (key == 's'  && d != U && d != D) {
                    d = D;
                } else if (key == 'a'  && d != R && d != L) {
                    d = L;
                } else if (key == 'w'  && d != U && d != D) {
                    d = U;
                }
            }
        }

        sprintf(score_s, "%d", score - 1);
        sprintf(sfps, "%d", fps);

        lib54cligc_pixel_text(1, 1, "score:", 45, 100, 235, 0, 0, 0);
        lib54cligc_pixel_text(8, 1, score_s, 45, 100, 235, 0, 0, 0);
        lib54cligc_pixel_text(13, 1, "FPS:", 45, 100, 235, 0, 0, 0);
        lib54cligc_pixel_text(18, 1, sfps, 45, 100, 235, 0, 0, 0);

        for (int i = 0; i < pms; i++){
            if (snake[i].a > 0){
                lib54cligc_pixel_add(snake[i].x, snake[i].y, 20, 200, 20);

                if (snake[i].x < 1 || snake[i].y < 1 || snake[i].x > (TERMINAL_SIZE.ws_col / 2) || snake[i].y > TERMINAL_SIZE.ws_row || (i > 0 && snake[0].x == snake[i].x && snake[0].y == snake[i].y)){
                    run = 0;
                }
            }
        }

        if ((tsec - tnow) / 1000 > 1){
            tnow = t();
            fps = ifps;
            ifps = 0;
        } else {
            ifps += 1;
        }

        handle_fruit();

        lib54cligc_pixel_add(fruit.x, fruit.y, 200, 20, 20);
        fflush(stdout);

        usleep(10000);
        lib54cligc_pixel_clear();
    }

    lib54cligc_quit();

    return 0;
}