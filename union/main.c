#include<stdio.h>

union AlphaNumber
{
    int number;
    char str[50];
} alphaNumber;


int main(){
    alphaNumber.number = 80;
    printf("\n%s\n", alphaNumber.str);
}