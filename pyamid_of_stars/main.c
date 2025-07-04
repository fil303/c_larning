#include<stdio.h>

int main(){
    int pyramid = 5;

    for(int row = 1; row <= pyramid; row++){
        for(int column = 1; column <= pyramid; column++){
            printf("*");
        }
    }
}