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

#define PORT 8765

int main() {
	int server_socket;
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

	// Integer to hold a potential client socket
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);
	if (client_socket < 0) {
		perror("Error in accepting");
		exit(1);
	}
	// send a message from the server
	char server_message[256] = "You have reached the server";
	if (send(client_socket, server_message, sizeof(server_message), 0) < 0) {
		perror("Error in sending");
		exit(1);
	}
	// Close the socket
	close(server_socket);

	return 0;
}
