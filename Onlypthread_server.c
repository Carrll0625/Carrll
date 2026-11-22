#include<server.h>

int Server_start(void){
	//网络初始化
	int server_sock;//服务端套接字
	int client_sock;//客户端套接字
	int client_io_array[1000];//存储客户端套接字数组
	struct sockaddr_in client_addr;
	socklen_t addrlen;
	char response[1500];
	int recvlen;
	char cip[16];
	time_t tp;
	char time_buf[1024];
	char* msg="Please try again\n";
	server_sock=Inet_init(NULL,PORT);
	for(int i=0;i<1000;i++)
		client_io_array[i]=-1;
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
			for(int i=0;i<1000;i++)
				if(client_io_array[i]==-1)
				{
					client_io_array[i]=client_sock;
					break;
				}
				bzero(cip,16);
				inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,cip,16);
				printf("server response:%s connect success , cport:%d\n",cip,ntohs(client_addr.sin_port));
				//首次相应
				first_response(client_sock,cip);
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
		for(int i=0;i<1000;i++)
		{
			if(client_io_array[i]!=-1)
			{
				bzero(response,sizeof(response));
				if((recvlen=recv(client_io_array[i],response,sizeof(response),MSG_DONTWAIT))>0)
				{
					//检测字节流是否为time
					response[strlen(response)-1]='\0';
					if(strcmp(response,"time")==0)
					{
						tp=time(NULL);
						bzero(time_buf,sizeof(time_buf));
						ctime_r(&tp,time_buf);	
						send(client_io_array[i],time_buf,sizeof(time_buf),MSG_NOSIGNAL);	
					}else
					{
						send(client_io_array[i],msg,strlen(msg),MSG_NOSIGNAL);	
					}
					
				}else if(recvlen==0)
				{
					//客户端断开链接
					printf("client exit,close sock:%d\n",client_io_array[i]);
					close(client_io_array[i]);
					client_io_array[i]=-1;
					
				}else
				{
					if(errno==EAGAIN)
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
		 
	}
	
}

int main(void)
{
	Server_start();
	return 0;
}


