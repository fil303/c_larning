#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef void (* JobFunction)(void*);

typedef struct Job {
    JobFunction fn;
    void* arg;
    struct Job* next;
} Job;

Job* head = NULL;

void print_loop_number(void* arg){
    int n = *(int*) arg;
    printf("Looped Number is: %d \n", n);
    free(arg);
}

void print_message(void* arg){
    char* message = (char*) arg;
    printf("Message : %s \n", message);
    // free(arg);
}

void add_job(JobFunction fn, void* arg){
    Job* job = malloc(sizeof(Job));
    job->fn = fn;
    job->arg = arg;
    job->next = NULL;

    pthread_mutex_lock(&lock);
    Job* tail = head;
    if(!tail){
        head = job;
    } else {
        while(tail->next) tail = tail->next;
        tail->next = job;
    }

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
}

void* worker_handler(void* _){
    while (1){
        pthread_mutex_lock(&lock);
        while(!head){
            pthread_cond_wait(&cond, &lock);
        }

        Job* job = head;
        head = head->next;
        pthread_mutex_unlock(&lock);

        job->fn(job->arg);
        free(job);
    }

    return NULL;
}

int main(){
    pthread_t worker;
    pthread_create(&worker, NULL, worker_handler, NULL);

    for(int i = 0; i <= 5; i++){
        int* num = malloc(sizeof(int));
        *num = i;

        add_job(print_loop_number, num);
    }

    char* msg = "Hello, Bro";
    add_job(print_message, msg);

    sleep(1);
    // pthread_join(worker, NULL);
    return 0;
}











// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>

// // Define job function pointer type
// typedef void (*JobFunction)(void*);

// // Struct for a job node in the queue
// typedef struct Job {
//     JobFunction func;
//     void* arg;
//     struct Job* next;
// } Job;

// Job* head = NULL;
// pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// // Sample job functions
// void print_number(void* arg) {
//     int n = *(int*)arg;
//     printf("Number: %d\n", n);
//     free(arg); // Remember to free!
// }

// void print_message(void* arg) {
//     char* msg = (char*)arg;
//     printf("Message: %s\n", msg);
//     free(msg);
// }

// // Worker thread: runs jobs from queue
// void* worker_thread(void* _) {
//     while (1) {
//         pthread_mutex_lock(&lock);
//         while (!head) {
//             pthread_cond_wait(&cond, &lock);
//         }

//         Job* job = head;
//         head = head->next;
//         pthread_mutex_unlock(&lock);

//         job->func(job->arg); // Run job
//         free(job);
//     }
//     return NULL;
// }

// // Add a job to the queue
// void add_job(JobFunction func, void* arg) {
//     Job* job = malloc(sizeof(Job));
//     job->func = func;
//     job->arg = arg;
//     job->next = NULL;

//     pthread_mutex_lock(&lock);
//     Job* tail = head;
//     if (!tail) {
//         head = job;
//     } else {
//         while (tail->next) tail = tail->next;
//         tail->next = job;
//     }
//     pthread_cond_signal(&cond);
//     pthread_mutex_unlock(&lock);
// }

// int main() {
//     pthread_t worker;
//     pthread_create(&worker, NULL, worker_thread, NULL);

//     // Add a number job
//     for (int i = 0; i < 5; i++) {
//         int* num = malloc(sizeof(int));
//         *num = i;
//         add_job(print_number, num);
//     }

//     // Add a message job
//     char* msg = strdup("Hello from job system!");
//     add_job(print_message, msg);

//     sleep(1); // Let worker finish
//     return 0;
// }
