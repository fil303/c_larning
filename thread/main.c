#include<stdio.h>
#include<threads.h>

thread_local int counter = 0;

int increase_counter(void* arg){
    int id = *(int*)arg;
    // thrd_sleep(10,1);
    counter = counter + id;

    printf("Thread %d: counter = %d\n", id, counter);
    return 0;
}

int main(){
    thrd_t t1, t2;
    int id1 = 1, id2 = 2;

    thrd_create(&t1, increase_counter, &id1);
    thrd_create(&t2, increase_counter, &id2);

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);

    return 0;
}