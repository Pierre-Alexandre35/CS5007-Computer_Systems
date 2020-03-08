//IMPORTANT COMPILE with : g++ -Wall shell.c -o shell

#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <pwd.h>
#include <signal.h>

/* The array below will hold the arguments: params[0] is the command. */
static char* params[512];
pid_t pid;
pid_t pidId;
int command_pipe[2];
int newLine[1000];
int oldLine[1000];
int jump;

#define READ  0
#define WRITE 1

static void currentFolder(int old, int path){
	char*recent_path;
	recent_path = NULL;
	//	set_glob("old directory", pwd)->pwd, 3);??
	//
	if(recent_path = NULL){
		free(recent_path);
		recent_path = NULL;
}	
}

//Execute commands pipe properly 
static int execCommand(int tempFlag, int p1, int p2)
{
    //parameters for piping
    int pipeParams[2];
    
    /* Piping */
    pipe( pipeParams );

    // create new child
    pid = fork();
   
    //if the process id is 0 (child)
    if (pid == 0){
        if ( p1 == 1 && p2 == 0 && tempFlag == 0){
        

            dup2( pipeParams[WRITE], STDOUT_FILENO );
        }
		else if (p1 == 0 && p2 == 0 && tempFlag != 0) 
		{
            
            dup2(tempFlag, STDIN_FILENO);
            dup2(pipeParams[WRITE], STDOUT_FILENO);
        } else 
		{
            // first command
            dup2( tempFlag, STDIN_FILENO );
        }
        
	//if(excevp(params[i],params) == 0
	//_exit(EXIT_FAILURE);

        if (execvp( params[0], params) == -1)
            _exit(EXIT_FAILURE); 
    }
    //if the temp flag is not egal to 0 then we can close the temp flag
    if (tempFlag != 0)
        close(tempFlag);
    
    //Close pipe for write 
    close(pipeParams[WRITE]);
    
    //If P2 command then close pipe for read  
    if (p2 == 1)
        close(pipeParams[READ]);
    
    return pipeParams[READ];
}

static int runCommand(char* command, int tempFlag, int p1, int p2);
static char usrtempFlag[1000];
static int n = 0; /* number of calls to 'command' */
static char newFlag[1000];
char machname[256];
char* path;
int status;
//Driver entry program 	
int main(int argc,char*argv[])
{
    printf("//Welcome to Pierre-Alexandre Mini SHell\\\n");
    printf("You can enter 'exit' or send ctrl+c to exit.\n");

	// get cwd for the path 
	path=getcwd(NULL,255);
	gethostname(machname,255);
	
    while (1) 
	{
        
		//Print the working directory 
	//	printf("@%s:%s>",machname,path);  	
	
		//new: print only >>
		printf("PA_Shelll>>>");
	
        fflush(NULL);
       

 
        /* Read a command usrtempFlag */
        if (!fgets(usrtempFlag, 1024, stdin))
            return 0;

	int p1 = 1;
	//temp varibales for the flag
	int temp;	        
        int tempFlag = 0;     

	// command used
        char* command = usrtempFlag;
        char* next = strchr(command, '|'); /* Find p1 '|' */
        
        while (next != NULL) 
		{
	    temp ++;
            /* 'next' points to '|' */
            *next = '\0';
            tempFlag = runCommand(command, tempFlag, p1, 0);
 
            command = next + 1;
            next = strchr(command, '|'); /* Find next '|' */
            p1 = 0;
        }
        tempFlag = runCommand(command, tempFlag, p1, 1);
		
        temp = 0;
	// next = strchr(command, "+")
	// remove that

	int i;


		for (i = 0; i < n; ++i)
			wait(NULL);
        n = 0;
    }
    return 0;
}



static int runCommand(char* command, int tempFlag, int p1, int p2)
{
   //Parse the command 
    while (isspace(*command)) command++;//Go over the white spaces if existed at p1 
     
    char* next = strchr(command, ' ');
    int i = 0;
    
// while there is still something to parse
    while(next != NULL) {
        next[0] = '\0';
        params[i++] = command;

//CHECKING FOR WHITE SPACE
//while(next = " ");
		
		while (isspace(*next)) next++;
        
        command = (next + 1);
        next = strchr(command, ' ');
    }
    
    if (command[0] != '\0') {
        params[i++] = command;
        //params[i] = command;
        next = strchr(command, '\n');
        next[0] = '\0';
    }
    
    params[i] = NULL;
	//////////////////////////////
	char stopChar;

	//Execute different commands 
	//Run speciail handlers for "cd" - "exit" - "Clear" - "kill"
    if (params[0] != NULL) 
	{
        if (strcmp(params[0], "exit") == 0)
            exit(0);
		else 
		{
			n += 1;
			if (strcmp(params[0], "Clear") == 0) //to add the clear functionality 
				strcpy(params[0],"clear");
			else 
			{
				if (strcmp(params[0], "help") == 0) //Help command
				{	
					printf("This is the helper. This program was create by Pierre-Alexandre. press q + enter to quit\n");
					fflush(NULL);
					stopChar = getchar();
					while(stopChar!='q')
					{
						stopChar = getchar();
					
					}
					fflush(NULL);
					 
					return 0;
				} 
				else 
				{
					if(strcmp(params[0],"cd") == 0) //Cd Command
					{
						if(chdir(params[1])!=-1)
							path=getcwd(NULL,255);
						else
							printf("cd: %s : No such file or directory\n",params[1]);		
						return 0;					
					}
					else if(strcmp(params[0],"kill") == 0) //Kill Command
						{
							pid=fork();
							if(pid==0)
							{
								execv("/bin/kill",params);
								exit(status);
							}
							else if(pid>=1)
							{
								waitpid(pid,&status,0);
							}	
						}	
				}
					
			}
			return execCommand(tempFlag, p1, p2);
		}
    }
    return 0;
}


 
 

