#include<server.h>

int Server_start(void){
	//网络初始化
	int server_sock;//服务端套接字
	int client_sock;//客户端套接字
	pid_t pid;//多进程服务器
	struct sockaddr_in client_addr;
	socklen_t addrlen;
	char response[1500];
	int recvlen;
	char cip[16];
	time_t tp;
	char time_buf[1024];
	char* msg="Please try again\n";
	server_sock=Inet_init(NULL,PORT);
	//将服务端套接字转换为非阻塞态
	int flag;
	flag=fcntl(server_sock,F_GETFL);
	flag|=O_NONBLOCK;
	fcntl(server_sock,F_SETFL,flag);
	printf("server [%s] ACCERTING....\n",SERVER_IP);
	while(1)
	{
		addrlen=sizeof(client_addr);
		if((client_sock=accept(server_sock,(struct sockaddr*)&client_addr,&addrlen))>0)
		{
				pid=fork();
				if(pid>0)
				{}
				else if(pid==0)
				{   
					bzero(cip,16);
					inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,cip,16);
					printf("server response:%s connect success , cport:%d\n",cip,ntohs(client_addr.sin_port));
					//首次相应
					first_response(client_sock,cip);

					while(1)
					{
					bzero(response,sizeof(response));
					if((recvlen=recv(client_sock,response,sizeof(response),0))>0)
					{
						//检测字节流是否为time
						response[strlen(response)-1]='\0';
						if(strcmp(response,"time")==0)
						{
							tp=time(NULL);
							bzero(time_buf,sizeof(time_buf));
							ctime_r(&tp,time_buf);	
							send(client_sock,time_buf,sizeof(time_buf),0);	
						}else
							{
								send(client_sock,msg,strlen(msg),0);	
							}
					
					}else if(recvlen==0)
						{
							//客户端断开链接
							printf("client exit,close sock:%d\n",client_sock);
							close(client_sock);
							exit(0);
						}else
							{
								if(errno=EAGAIN)
									{
										//unblock
									}
								else
									{
										perror("recv msg failed");
										exit(0);
									}
							}
					}
				}
				else{
					perror("create process failed");
					exit(0);
					}
		}else if(client_sock== -1)
		{
			if(errno==EAGAIN)
			{//unblock 
			}
			else
			{
				perror("accept call failed");
				exit(0);
			}
		}
	}
}

int main(void)
{
	Server_start();
	return 0;
}


