// Note: I recommend implementing the tcpserver.c first.
//
// Compile with: gcc tcpclient.c -o tcpclient
//
// Implement tcp client below.


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
        char cmd[1000];
	int client_socket;
	if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error.\n");
	}

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET; // 32-bit IPV4 address
	server_address.sin_port = htons(PORT); // convert to the appropriate port number using htons
	server_address.sin_addr.s_addr = htons(INADDR_ANY); // Our ip address, which is localhost using INADDR_ANY

	int connection_status;
	if( (connection_status = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address))) <0 ){
		printf("%d Connection unsuccessful\n", connection_status);
		close(client_socket);
		exit(0);	
	}else{
		printf("Connected successfully\n");
	}



        int stop = 0;

	//while the client is still connected
        while(!stop) {


		printf("Enter command to execute on server: ");
		fgets(cmd, sizeof(cmd), stdin);	                  
		cmd[strlen(cmd)-1] = 0; // remove \n

		if (send(client_socket, cmd, strlen(cmd) + 1, 0) < 0) {
			perror("Error in sending");
			exit(1);
		}
		//if the user type exit then we are stopping the server	

		if(!strcmp(cmd, "exit")) {
			stop = 1;
		}
                else {
			//store the server variable in a new char
			char server_response[256];
			
			//receiving the message from the user 
			recv(client_socket, &server_response, sizeof(server_response), 0);
			
			//print out what the user type as instructions
			printf("The server sent those instructions: %s\n",server_response);
		}
	}

	close(client_socket);
	return 0;
}


