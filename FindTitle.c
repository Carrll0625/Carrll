#include<stdio.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>
int main()
{
	//1.打开映射文件
	int fd = open("url.txt",O_RDWR);
	//2.获取文件大小
	int fsize= lseek(fd,0,SEEK_END);
	//文件映射
	char* mmap_ptr=NULL;
	mmap_ptr=mmap(NULL,fsize,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
	//关闭文件
	close(fd);
	//正则匹配所有的地址
	regex_t  reg;
	char* regstr="title=\\([^<]\\+\\)";
	regcomp(&reg,regstr,0);
	regmatch_t match[2];
	char word[1024];
	while(regexec(&reg,mmap_ptr,2,match,0)==0)
	{
		snprintf(word,match[1].rm_eo-match[1].rm_so+1,"%s",mmap_ptr+match[1].rm_so);
		mmap_ptr+=match[0].rm_eo; 
		printf("%s\n",word);
	}


	return 0;
}

