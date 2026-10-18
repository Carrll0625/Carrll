#include<copy.h>
int main(int argc ,char** argv)
{
	//拷贝任务
	int recfd=open(argv[1],O_RDONLY);
	int destfd=open(argv[2],O_WRONLY|O_CREAT,0664);
	//指针偏移
	int offset=atoi(argv[3]);
	lseek(recfd,offset,SEEK_SET);
	lseek(destfd,offset,SEEK_SET);
	int blocksize=atoi(argv[4]);
	char buffer[blocksize];
	bzero(buffer,sizeof(buffer));
	int len=read(recfd,buffer,sizeof(buffer));
	write(destfd,buffer,len);
	
	//读写完毕后关闭文件读取
	close(recfd);
	close(destfd);
	//结束本次进程
	exit(0);
	return 0;	
}
