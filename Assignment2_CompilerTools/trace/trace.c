#include <stdio.h>
#include <time.h>

//count is the total number of functions calls.
//start is when we are calling the function.
// end is when the function stops.
// totalTime is how much time all of these functions takes to execute
int count = 0;
time_t start;
time_t end;
double timePerFunction;
double totalTime;


// Increasing the count of function execution everytime and starting the timer in the function. 
__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *this_fn, void *call_site){
	count ++;
	time(&start);
	printf("Function entered\n");

}

//Closing the time in that function.
//Then, we are using the difftime function to calculate the difference between the end and the start of the time.
__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *this_fn, void *call_site){ 	
        time(&end);
	timePerFunction = difftime(end,start);
        totalTime += timePerFunction;
	printf("Function exited\n");
}

