// Take a look at some of the previous examples to create your own program!
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

	char* myargv[16];	
	myargv[0]="example5";
	myargv[1]="-F";
	myargv[2]=NULL;

	if (fork() == 0) {
		execve(myargv[0],myargv,NULL);

		printf("Child: Should never get here\n");
		exit(1);
	}else {
		wait(NULL);
		if (fork() == 0) {
			myargv[0]="/bin/ps";
			myargv[1]=NULL;
			myargv[2]=NULL;

			execve(myargv[0],myargv,NULL);

			printf("Child: Should never get here\n");
			exit(1);
		} else {
			wait(NULL);
			if (fork() == 0) {
				myargv[0]="/bin/pwd";
				myargv[1]=NULL;
				myargv[2]=NULL;

				execve(myargv[0],myargv,NULL);

				printf("Child: Should never get here");
				exit(1);
			} else {
				wait(NULL);
			}
		}

		wait(NULL);
		printf("This always prints last\n");
	}
	return 0;
}
