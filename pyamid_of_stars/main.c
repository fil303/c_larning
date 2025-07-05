#include<stdio.h>

void right_to_left_pyramid(int length){
    int pyramid_row = length;

    for(int row = 1; row <= pyramid_row; row++){
        for(int column = 1; column <= row; column++){
            printf("*");
            if(column == row) printf("\n");
        }

    }
}

void left_to_right_pyramid(int length){
    int pyramid_row = length;

    for(int row = 1; row <= pyramid_row; row++){
        for(int column = 1; column <= pyramid_row; column++){
            int empty_col_in_row = pyramid_row - row;

            if(empty_col_in_row < column)
                printf("*");
            else
                printf(" ");

            if(column == pyramid_row) printf("\n");
        }

    }
}

void center_pyramid(int length){
    int pyramid_col = length;
    int pyramid_row = length - 2;

    for(int row = 1; row <= pyramid_row; row++){
        for(int column = 1; column <= pyramid_col; column++){
            int empty_col_in_row = pyramid_row - row;
            int printable_col    = pyramid_col - empty_col_in_row;

            if(
                empty_col_in_row < column
                && printable_col >= column
            )   printf("*");
            else printf(" ");

            if(column == pyramid_col) printf("\n");
        }
    }
}

int main(){
    right_to_left_pyramid(10);
    left_to_right_pyramid(10);
    center_pyramid(15);
    return 0;
}