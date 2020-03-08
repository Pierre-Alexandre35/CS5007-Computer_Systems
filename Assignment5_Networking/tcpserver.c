// Compile with: gcc tcpserver.c -o tcpserver
//
// Implement tcp server below.
// Our standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Some types and unix operations
#include <sys/types.h>
#include <unistd.h>

// A sockets library and internet protocol library
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8761

int main() {
	int server_socket;
	pid_t pid;
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Error in creating socket");
		exit(1);
	}
	
	struct sockaddr_in server_address;
	
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = htons(INADDR_ANY);

	if (bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) {
		perror("Error in binding");
		exit(1);
	}
	printf("Server bind()\n");
	
	if (listen(server_socket, 27) != 0) {
		perror("Error in listening");
		exit(1);
	}


        while(1) {
		// Integer to hold a potential client socket
		int client_socket;
		client_socket = accept(server_socket, NULL, NULL);
		if (client_socket < 0) {
			perror("Error in accepting");
			exit(1);
		}
	        printf("Client has joined: %d\r\n", client_socket);

                /* Create child process */
                pid = fork();
		
                if (pid < 0) {
			perror("ERROR on fork");
			exit(1);
                }
      
                if (pid == 0) {
			/* This is the client process */
			//close(server_socket);

	        	char cmd[1000];
	        	do {
				//fill up the cmd with a constant byte of the size of that cmd
			        memset(cmd, 0, sizeof(cmd));
			
			        recv(client_socket, cmd, sizeof(cmd), 0);
				printf("Received from %d:\n", client_socket);
	        		printf("%s\n", cmd);
                        	//if the command entered is exit 
				if (strcmp(cmd, "exit")) {
			        	system(cmd);  
                                        printf("Sending response\n");
					// send a message from the server
					char server_message[256] = "Executed";
					//If send is less than 0 (that means there is an error), we exit
					if (send(client_socket, server_message, sizeof(server_message), 0) < 0) {
						perror("Error in sending");
						exit(1);
					}
				}
			}
			// while the command is exit then we are closing the client socket
			while(strcmp(cmd, "exit"));

			close(client_socket);
                }
                else {
			//close(client_socket);
                }
	}
	// Close the socket
	close(server_socket);

	return 0;
}
