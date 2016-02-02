#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<unistd.h>
#include <errno.h>

#include "openflow/openflow.h"
#include "openflow/ofptype.h"
#include "view/dump.h"

#define MY_PORT		6633
#define MAXBUF		1024

int main()
{
    int sockfd;
	struct sockaddr_in self;
	char servermessage[MAXBUF];
	char buffer[MAXBUF];

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

		/*---Echo back anything sent---*/
	 	// Hello message from switch
	 	//01 00 00 08 00 00 00 cb
	 	socklen_t read_size;
		while((read_size = recv(clientfd, buffer, MAXBUF, 0))>0){
			printf("%s:%d send\r\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			dump((unsigned char*)buffer,0,read_size);
            getOFP_TYPE(buffer[1]);
			if(buffer[1]==OFPT_HELLO){
				servermessage[0] =0x01;
				servermessage[1] =OFPT_HELLO;
				servermessage[2] =0x00;
				servermessage[3] =0x08;
				servermessage[4] =0x00;
				servermessage[5] =0x00;
				servermessage[6] =0x00;
				servermessage[7] =buffer[7];
                printf("Controller send hello back\r\n");
				send(clientfd, servermessage, 8, 0);
			}else if(buffer[1]==OFPT_ECHO_REQUEST){
                servermessage[0] =0x01;
                servermessage[1] =OFPT_ECHO_REPLY;
                servermessage[2] =0x00;
                servermessage[3] =0x08;
                servermessage[4] =0x00;
                servermessage[5] =0x00;
                servermessage[6] =0x00;
                servermessage[7] =buffer[7];
                printf("Controller send echo reply\r\n");
                send(clientfd, servermessage, 8, 0);    
            }else if(buffer[1]==OFPT_PACKET_IN){
                //struct ofp_packet_in *ofp_packet_in_=(struct ofp_packet_in*)(buffer);          
                printf("buffer_id: %02x%02x%02x%02x\r\n",buffer[8],buffer[9],buffer[10],buffer[11]);
                printf("total_len: %02x%02x\r\n",buffer[12],buffer[13]);
                printf("in_port  : %02x%02x\r\n",buffer[14],buffer[15]);
            }
		}
	 	if(read_size == 0)
		{
			printf("%s:%d disconnected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			fflush(stdout);
		}
	 	
		/*---Close data connection---*/
		close(clientfd);
	}

	/*---Clean up (should never get here!)---*/
	close(sockfd);
	return 0;
}
