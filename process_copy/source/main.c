#include<copy.h>

int main(int argc,char** argv)
{
  int pronum=1;
  if(argv[3]!=0)
  {
	pronum=atoi(argv[3]);	  
  }
	if(check_pram(argc,argv[1],pronum)==-1)
	{
		return -1;	
		
	}
	int blocklen=block_cur(argv[1],pronum);
	if(process_create(argv[1],argv[2],pronum,blocklen)==-1)
	{
			return -1;
	}
	process_wait();
	return 0;
	
}
