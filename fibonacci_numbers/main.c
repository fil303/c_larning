#include<stdio.h>

int main(){
    int size = 10, first = 0, last = 1, next;

    for(int i = 0; i < size; i++){

        if(i <= 1)
            next = i;
        else{
            next = first + last;
            first= last;
            last = next;
        }

        printf("%d ", next);
    }
    printf("\n");

    return 0;
}