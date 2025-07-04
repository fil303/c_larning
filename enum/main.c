#include<stdio.h>

enum Books {
    BANGLA,
    ENGLISH,
    MATH,
};

enum Class {
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10
};

int main(){
    enum Class class = NINE;
    enum Books book = MATH;

    if(class == NINE && book == MATH){
        printf("I do not want to go school");
    } else {
        printf("I love my school");
    }
}