#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>

struct termios orig_term;

void restore_terminal(){
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
}

void set_raw_mode(){
    struct termios raw;
    tcgetattr(STDIN_FILENO, &orig_term);
    atexit(restore_terminal); // Restore on exit

    raw = orig_term;
    raw.c_lflag &= ~(ICANON | ECHO); // Turn off line buffering and echo
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

int main(){
    set_raw_mode(); // Set terminal to raw input mode

    struct pollfd pfd = {
        .fd     = STDIN_FILENO,
        .events = POLLIN
    };

    printf("⏳ Press any key within 5 seconds...\n");

    int ret = poll(&pfd, 1, 5000); // wait up to 5000 ms (5 seconds)

    if(ret == -1){
        perror("Poll Failed !!!");
        exit(1);
    } else if (ret == 0){
        printf("⏱️ Timeout: no key was pressed.\n");
    } else {
        char c;
        read(STDERR_FILENO, &c, 1);
        printf("✅ You pressed: '%c'\n", c);
    }

    return 0;
}