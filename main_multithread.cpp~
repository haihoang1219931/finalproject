#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<unistd.h>
#include <errno.h>
#include<pthread.h>

#include "openflow/openflow.h"
#include "openflow/ofptype.h"
#include "view/dump.h"

#define MY_PORT		6633
#define MAXBUF		1024
void *connection_handler(void *clientfd){
	char servermessage[MAXBUF];
	char buffer[MAXBUF];
	socklen_t read_size;
	int sock = *(int*)clientfd;
	while((read_size = recv(sock, buffer, MAXBUF, 0))>0){
		/*
		printf("%s:%d send\r\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		dump((unsigned char*)buffer,0,read_size);
		getOFP_TYPE(buffer[1]);
		*/
	}
	if(read_size == 0)
	{
		//printf("%s:%d disconnected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		puts("Disconnected\r\n");
		fflush(stdout);
	}

	/*---Close data connection---*/
	close(sock);
}
int main()
{
    int sockfd;
	struct sockaddr_in self;
	

	/*---Create streaming socket---*/
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}

	/*---Initialize address/port structure---*/
	bzero(&self, sizeof(self));
	self.sin_family = AF_INET;
	self.sin_port = htons(MY_PORT);
	self.sin_addr.s_addr = INADDR_ANY;

	/*---Assign a port number to the socket---*/
    if ( bind(sockfd, (struct sockaddr*)&self, sizeof(self)) != 0 )
	{
		perror("socket--bind");
		exit(errno);
	}

	/*---Make it a "listening socket"---*/
	if ( listen(sockfd, 20) != 0 )
	{
		perror("socket--listen");
		exit(errno);
	}

	/*---Forever... ---*/
	while (1)
	{	int clientfd;
		struct sockaddr_in client_addr;
		socklen_t addrlen=sizeof(client_addr);
		
		/*---accept a connection (creating a data pipe)---*/
		clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
		printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		puts("Connection accepted");
        pthread_t thread_id;
        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &clientfd) < 0)
        {
            perror("could not create thread");
            return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        pthread_join( thread_id , NULL);
        puts("Handler assigned");
		/*---Echo back anything sent---*/
	 	// Hello message from switch
	 	//01 00 00 08 00 00 00 cb
	 	
	}

	/*---Clean up (should never get here!)---*/
	close(sockfd);
	return 0;
}
