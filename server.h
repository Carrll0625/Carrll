#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#define SERVER_IP "192.168.58.128"
#define PORT 7891
#define BACK_LOG 256
int Inet_init(char * ip,int port)
{
	int sockfd;
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
		perror("sock create failed");
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	if(!ip)
		addr.sin_addr.s_addr=INADDR_ANY;
	else
		addr.sin_addr.s_addr=inet_pton(AF_INET,ip,&addr.sin_addr.s_addr);
	if((bind(sockfd,(struct sockaddr*)&addr,sizeof(addr)))==-1)
	 	perror("bind create failed");
	if((listen(sockfd,BACK_LOG))==-1)
		perror("listen create failed");

	return sockfd;

}

int first_response (int sockfd,char* cip)
{
	char response[4096];
	bzero(response,sizeof(response));
	sprintf(response,"Hi,[%s] connect success",cip);
	send(sockfd,response,sizeof(response),MSG_NOSIGNAL);
	return 0;
	
}

