#include <server.h>

void create_selectserver()
{
	int client_sock;
	int server_sock;
	int sock_io[1000];
	int sockNum;
	char response[1500];
	int recvlen;
	char cip[16];
	time_t tp;
	char time_buf[1024];
	struct sockaddr_in client_addr;
	char *msg="Please try again\n";
	socklen_t socklen;
	server_sock=Inet_init(NULL,PORT);
	sock_io[0]=server_sock;
	for(int i=1;i<1000;i++)
	{
		sock_io[i]=-1;
	}
	fd_set set,oset;
	FD_ZERO(&set);
	FD_SET(server_sock,&set);
	int flag;
	flag=fcntl(server_sock,F_GETFL);
	flag|=O_NONBLOCK;
	fcntl(server_sock,F_SETFL,flag);
	sockNum=server_sock;
	printf("The server is running....\n");
	while(1)
	{   
		socklen=sizeof(client_addr);
		if((client_sock=accept(server_sock,(struct sockaddr*)&client_addr,&socklen))>0)
		    {
			bzero(cip,16);
			inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,cip,16);
			printf("server response:%s connect success ,cport:%d\n",cip,ntohs(client_addr.sin_port));
			first_response(client_sock,cip);
			sockNum=client_sock;
			for(int i=1;i<1000;i++)
			{
				if(sock_io[i]==-1)
				{
					sock_io[i]=client_sock;
					FD_SET(sock_io[i],&set);
					break;
				}
			}
		}else
		{

		}

		int BackNum;
		oset=set;
		BackNum=select(sockNum+1,&set,NULL,NULL,NULL);
		if(BackNum>0)
		{
			for(int i=1;i<1000;i++)
			{
				if(sock_io[i]!=-1&&FD_ISSET(sock_io[i],&set))
				{
					bzero(response,sizeof(response));
					if((recvlen=recv(sock_io[i],response,sizeof(response),MSG_DONTWAIT))>0)
					{
						response[strlen(response)-1]='\0';
						if(strcmp(response,"time")==0)
						{
							tp=time(NULL);
							bzero(time_buf,sizeof(time_buf));
							ctime_r(&tp,time_buf);
							send(sock_io[i],time_buf,strlen(time_buf),MSG_NOSIGNAL);
						}
						else
							send(sock_io[i],msg,strlen(msg),MSG_NOSIGNAL);
					}
					else if(recvlen==0)
					{
						printf("client exit,close sock:%d\n",sock_io[i]);
						close(sock_io[i]);
						FD_CLR(sock_io[i],&oset);
						sock_io[i]=-1;
					}else
					{
						perror("recv msg failed");
						exit(0);
						}
				}
			}
		}
		set=oset;
	}		
}

int main(void)
{
	create_selectserver();	
    return 0;
}

