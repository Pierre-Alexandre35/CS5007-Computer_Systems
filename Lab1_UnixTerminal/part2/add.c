// Write a C program that calls an add function(long add(long a, long b).
#include <stdio.h>

long add(long a, long b){
    return a + b;
}

int main(){
    long sum = add(1, 9);
    return 0;
}
