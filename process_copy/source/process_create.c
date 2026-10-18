#include<copy.h>


int process_create(const char* srcfile,const char* destfile ,int pronum ,int blocksize)
{
   int i=0;
   pid_t pid;
   for(i;i<pronum;i++)
   {
	   pid=fork();
	   if(pid==0) break;
	   if(pid<0) return -1;
   }
   int setoff=i*blocksize;
   //接下来重载进程 用COPY
   char str_offset[10];
   char str_blocksize[10];
   bzero(str_offset,10);
   bzero(str_blocksize,10);
   sprintf(str_offset , "%d",setoff);
   sprintf(str_blocksize,"%d",blocksize);
   execl("/home/carrll/process_copy/Mod/COPY","./COPY",srcfile,destfile,str_offset,str_blocksize,NULL);
   return 0;
}
