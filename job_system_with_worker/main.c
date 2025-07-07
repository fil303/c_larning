#include <stdio.h>
#include <stdlib.h>

typedef void (* JobFuntion)(void*);

typedef struct Job {
    JobFuntion fn;
    void* arg;
    struct Job* next;
} Job;

void print_loop_number(void* arg){
    int n = *(int*) arg;
    printf("Looped Number is: %d \n", n);
    free(arg);
}

void add_job(JobFuntion fn, void* arg){
    
}

int main(){

    for(int i = 0; i <= 5; i++){
        int* num = malloc(sizeof(int));
        num = i;

        add_job(print_loop_number(num));
    }

    return 0;
}