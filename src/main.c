#include <stdio.h>
#include <emscripten.h>
#include <sys/ioctl.h>
#include <unistd.h>

static char buffer[256];
static int pos = 0;

static int counter = 0;

void loop() {
	printf("\b\r");
    printf("loop %d", counter);
	printf("\n");
	counter++;
}

void init() {
    printf("\033[?1049h");
    printf("\033[2J\033[H");
    printf("\033[?25l");
};
void cleanup() {
    printf("\033[?25h");
    printf("\033[?1049l");
};
void draw(int x, int y, const char* c) {
    printf("\033[%d;%dH", y + 1, x);
    printf(c);
}

void border(int xa, int ya, int w, int h, const char* c) {
    for (int x = xa; x < w + 1; x++) {
        draw(x, ya, c);
    }
    for (int y = ya + 1; y < h - 1; y++) {
        draw(xa, y, c);
        draw(w, y, c);
    }
    for (int x = xa; x < w + 1; x++) {
        draw(x, h - 1, c);
    }
    return;
}
void setcol(int r, int g, int b) { printf("\033[38;2;%d;%d;%dm", r, g, b); };
void setbg(int r, int g, int b) { printf("\033[48;2;%d;%d;%dm", r, g, b); };
void uncol() { printf("\033[0m"); }

int main() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int w_width, w_height;
    w_width = w.ws_col;
    w_height = w.ws_row;
	printf("Width: %d, Height: %d\n", w_width, w_height);
    w_width = 80;
	w_height = 24;
    init();
    setcol(50, 50, 50);
    setbg(255, 255, 255);
    const char* test = "$";
    border(0, 0, w_width, w_height, test);
    uncol();
    fflush(stdout);
    //getchar();
    //cleanup();
}