// Write a C program using the goto command and a label.
#include <stdio.h>

int main(){
    int i = 0;

    PRINT:
        printf("%d\n", i);
        i++;
        if(i < 10){
            goto PRINT; 
        }

    return 0;
}
