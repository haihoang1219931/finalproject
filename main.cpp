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
				servermessage[0] =buffer[0];
				servermessage[1] =OFPT_HELLO;
				servermessage[2] =buffer[2];
				servermessage[3] =0x08;
				servermessage[4] =buffer[4];
				servermessage[5] =buffer[5];
				servermessage[6] =buffer[6];
				servermessage[7] =buffer[7];
                printf("Controller send hello back\r\n");
				send(clientfd, servermessage, 8, 0);
                //send feature request to switch
                
                //send feature 
			}else if(buffer[1]==OFPT_ECHO_REQUEST){
                servermessage[0] =buffer[0];
                servermessage[1] =OFPT_ECHO_REPLY;
                servermessage[2] =buffer[2];
                servermessage[3] =buffer[3];
                servermessage[4] =buffer[4];
                servermessage[5] =buffer[5];
                servermessage[6] =buffer[6];
                servermessage[7] =buffer[7];
                printf("Controller send echo reply\r\n");
                send(clientfd, servermessage, 8, 0);    
            }else if(buffer[1]==OFPT_PACKET_IN){
                //struct ofp_packet_in *ofp_packet_in_=(struct ofp_packet_in*)(buffer);          
                printf("buffer_id: %02x%02x%02x%02x\r\n",(unsigned char)buffer[8],(unsigned char)buffer[9],(unsigned char)buffer[10],(unsigned char)buffer[11]);
                printf("total_len: %02x%02x\r\n",(unsigned char)buffer[12],(unsigned char)buffer[13]);
                printf("in_port  : %02x%02x\r\n",(unsigned char)buffer[14],(unsigned char)buffer[15]);
                printf("reason   : %02x\r\n",(unsigned char)buffer[16]);
                printf("pad      : %02x\r\n",(unsigned char)buffer[17]);
                printf("data     : %02x\r\n",(unsigned char)buffer[18]);
                printf("Controller send message packet out\r\n");
                //ofp_header
                servermessage[0] =buffer[0];
                servermessage[1] =OFPT_PACKET_OUT;
                servermessage[2] =buffer[2];
                servermessage[3] =24;
                printf("packet len: %d\r\n",servermessage[3]);
                servermessage[4] =buffer[4];
                servermessage[5] =buffer[5];
                servermessage[6] =buffer[6];
                servermessage[7] =buffer[7];
                //ofp_packet_out
                //buffer_id: 4
                servermessage[8] =buffer[8]; 
                servermessage[9] =buffer[9];
                servermessage[10] =buffer[10];
                servermessage[11] =buffer[11];
                printf("buffer_id       : %02x%02x%02x%02x\r\n",(unsigned char)servermessage[8],(unsigned char)servermessage[9],(unsigned char)servermessage[10],(unsigned char)servermessage[11]);
                //input port: 2
                servermessage[12] =buffer[14];
                servermessage[13] =buffer[15];
                printf("in_port         : %02x%02x\r\n",(unsigned char)servermessage[12],(unsigned char)servermessage[13]);
                //actions_length: 2
                servermessage[14] =0x00;
                servermessage[15] =0x08;
                printf("actions_length  : %02x%02x\r\n",(unsigned char)servermessage[14],(unsigned char)servermessage[15]);
                //ofp_action_header
                //type: 2
                servermessage[16] =0x00;
                servermessage[17] =OFPAT_OUTPUT;
                printf("action_type     : %02x%02x\r\n",(unsigned char)servermessage[16],(unsigned char)servermessage[17]);
                //len: 2
                servermessage[18] =0x00;
                servermessage[19] =0x08;
                printf("actions_len     : %02x%02x\r\n",(unsigned char)servermessage[18],(unsigned char)servermessage[19]);
                //pad: 4
                servermessage[20] = 0x00;
                servermessage[21] = 0x02;
                servermessage[22] = 0x00;
                servermessage[23] = 0x00;
                int z;
                for(z=0;z<buffer[13];z++){
                    servermessage[24+z]=buffer[18+z];
                }
                printf("data:\r\n");
                //dump((unsigned char*)servermessage,24,buffer[13]+24);
        
                send(clientfd, servermessage,servermessage[3],0);
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
