#include<copy.h>

int block_cur(const char* srcfile,int pronum)
{
 //先打开源文件计算源文件的大小
 int srcfd=open(srcfile,O_RDONLY);
 int len=lseek(srcfd,0,SEEK_END);
 int block_size=len/pronum+1;
 return block_size;
}
