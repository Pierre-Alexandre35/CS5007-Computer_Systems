// Write a C program called array2.c that has an array of 400 integers in the function of main that is dynamically allocated.
#include <stdio.h>
#include <stdlib.h>

int main(){
    int* num = malloc(sizeof(int) * 400);

    num[0] = 10;
    num[10] = 150;
    num[50] = 800;
    num[250] = 9999;

    return 0;
}
