#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t canceled = 0;

void run_on_exit(){
    if(canceled){
        printf("Count Down Closed By User !!! \n");
    }else{
        printf("Count Down Closed Normally \n");
    }
}

void handel_int(int sig){
    canceled = 1;
    printf("Canceled this count down!!!!!!! \n");
    exit(0);
}

void handel_alarm(int sig){
    printf("Count Down Started Alarm!!!! \n");
    exit(0);
}

int main(){
    atexit(run_on_exit);
    signal(SIGINT, handel_int);
    signal(SIGALRM, handel_alarm);

    int seconds = 10;
    printf("Count down started from %d \n", seconds);
    alarm(seconds);

    for (int i = seconds; i > 0; i--) {
        printf("Remain seconds : %d \n", i);
        sleep(1);
    }
    return 0;
}