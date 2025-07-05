#include <stdio.h>
#include <stdlib.h>
int reversed_number, last_digit;

int revers_number_func(int number){
    if(number == 0 && reversed_number) return reversed_number;
    if(!number) return 0;

    last_digit = number%10;
    reversed_number = reversed_number*10+last_digit;

    return revers_number_func(number/10);
}

int main(){
    int number = 89548;
    int revers_number;

    revers_number = revers_number_func(number);
    printf("Number : %d \n", number);
    printf("Reversed Number : %d \n", revers_number);
    return 0;
}