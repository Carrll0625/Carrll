#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/wait.h>

#define msg "son process is running....\n"

int main(void)
{
  int fds[2];
  pipe(fds);
  //创建5个子进程
  int i=0;
  pid_t pd;
  for(i;i<5;i++)
  {
   	  pd=fork();
	  if(pd==0) break;
  }
  if(pd>0)
  {
	char buffer[4096];
	bzero(buffer,sizeof(buffer));
    //关闭写端 只保留读端
	close(fds[1]);
	while(1)
	{
	  read(fds[0],buffer,sizeof(buffer));	
	  
	}
  }else if(pd==0)
   {
	   close(fds[0]);
     while(1)
	 {
	  write(fds[1],msg,strlen(msg));	 
	 }
	  
   }else
  {
   perror("create process failed.");	  
  }
	
}
