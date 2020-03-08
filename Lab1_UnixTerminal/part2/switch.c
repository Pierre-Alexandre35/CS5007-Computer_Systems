// Write a C program using a switch statement
#include <stdio.h>

int main(){
    int rank = 1;
    
    switch(rank){
        case 1:
            puts("Awesome!");
            break;
        case 2:
            puts("Good job!");
            break;
        case 3:
            puts("You made it!");
            break;
        default:
            puts("Nice try :)");
    }

    printf("Your rank is: %d\n", rank);

    return 0;
}
