#include "stdio.h"
#include "time.h"

//Count, timePerFunction and totalTime are external functions.
extern int count;
extern double timePerFunction;
extern double totalTime; 

//When we are calling the msg function, that function is going to be innactive for 1 second before to end. 
void msg(){
    printf("Hello\n");
    sleep(1);
}


int main(){
    int i;
    
    //iterating 10 times over the function msg
    for(i = 0 ; i < 10 ; i++){
        msg();
    printf("Total functions called now: %d\n", count); 
    printf("Time for that function in seconds: %f\n",timePerFunction);
    }

   //The total time to run the program is the total number of iterations + the first call which was not part of the iteration.
    totalTime = totalTime + timePerFunction;
    printf("Total cummulated time in seconds: %f\n", totalTime);
    return 0;
}

