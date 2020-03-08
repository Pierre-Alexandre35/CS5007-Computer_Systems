#include<stdio.h>
#include<string.h>

//This is a single line parser. 
int main(){

    //creating a char array to store the list of instructions up to 1000 characters.  
    char instructions[1000];
    printf("Type a list of instructions\n");
	
    //supply fgets with instructions up to 1000 characters and store the user input (list of instructions). 
    fgets(instructions,1000, stdin);

    //strtok divides the instruction string into individual tokens everytime we are reaching a new white space. 
    char *command = strtok(instructions, " ");
 
    //We are printing each token (command) on a new line until the end of the instructions. 
    while(command != NULL){
        printf("%s\n",command);
        command = strtok(NULL, " ");
    }
    return 0;
}
