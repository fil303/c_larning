#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void work_with_select(){
    printf("Start working with select \n");

    fd_set readFds;
    FD_ZERO(&readFds);
    FD_SET(STDIN_FILENO, &readFds);

    struct timeval tv;
    tv.tv_sec = 5;

    int ready = select(STDIN_FILENO + 1, &readFds, NULL, NULL, &tv);
    printf("select return: %d \n", ready);
    if(ready == -1){
        printf("got Error \n");
    } else if (ready == 0){
        printf("got Timeout \n");
    } else {
        printf("got Something \n");
        if(FD_ISSET(STDIN_FILENO, &readFds)){
            char buffer[100];
            if(fgets(buffer, sizeof(buffer), stdin)){
                buffer[strcspn(buffer, "\n")] = '\0';
                printf("✅ You typed: %s\n", buffer);
            }
        }
    }
    exit(0);
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>   
// #include <sys/select.h>
// #include <string.h>

// int main() {
//     fd_set readfds;             // Set of fds to watch 
//     struct timeval tv;          // Timeout struct

//     printf("⌨️  Type something within 5 seconds:\n");

//     // 1. Prepare fd set
//     FD_ZERO(&readfds);          // clear set
//     FD_SET(STDIN_FILENO, &readfds); // add stdin (fd = 0)

//     // 2. Set timeout to 5 seconds
//     tv.tv_sec = 5;
//     tv.tv_usec = 0;

//     // 3. Call select
//     int ready = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

//     if (ready == -1) {
//         perror("select error");
//         exit(1);
//     } else if (ready == 0) {
//         printf("⏱️  Timeout: no input detected.\n");
//     } else {
//         if (FD_ISSET(STDIN_FILENO, &readfds)) {
//             char buffer[100];
//             if (fgets(buffer, sizeof(buffer), stdin)) {
//                 // strip newline
//                 buffer[strcspn(buffer, "\n")] = '\0';
//                 printf("✅ You typed: %s\n", buffer);
//             }
//         }
//     }

//     return 0;
// }

