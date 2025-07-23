#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(){
    const char* file_name = "demo_text_file.txt";

    int fd = open(file_name, O_RDONLY);

    if(fd == -1){
        perror("Failed to open file");
        return 1;
    }

    struct stat sb;
    if(fstat(fd, &sb) == -1){
        perror("File size get failed");
        return 1;
    }

    void* mapped = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(mapped == MAP_FAILED){
        perror("File mapped failed");
        close(fd);
        return 1;
    }

    write(STDOUT_FILENO, mapped, sb.st_size);

    munmap(mapped, sb.st_size);
    close(fd);
    return 0;
}