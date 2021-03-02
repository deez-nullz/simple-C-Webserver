// Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080  // the port users will be connecting to

int main(int argc, char const *argv[]) 
{
    int server_fd, new_socket; long valread; // listen on server_fd, new connection on new_socket
    struct sockaddr_in their_addr; // connector's address information
    
    zchar *hello = "Hello from server";
    
    // Creating socket file descriptor,     /* First call to socket() function */
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    
   /* Initialize socket structure */
    address.sin_family = AF_INET; // host byte order 
    address.sin_addr.s_addr = INADDR_ANY; // AF_INET or AF_INET6 to force version
    address.sin_port = htons( PORT );  // short, network byte order 
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);  // memset(&(their_addr.sin_zero), '\0', 8);  // zero the rest of the struct 
    
       // Bind socket to local address
    // -----------------------------------------------------------------------------------------------------------------
    // bind() assigns the address specified by serverAddress to the socket referred to by the file descriptor serverSocket.
    
    /* Now bind the host address using bind() call.*/
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
       
   /* Now start listening for the clients, here process will
      * go in sleep mode and will wait for the incoming connection
   */
   
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
        // Wait for a connection, create a connected socket if a connection is pendin
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        write(new_socket , hello , strlen(hello));
        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
    }
    return 0;
} 
