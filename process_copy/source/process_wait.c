#include<copy.h>
int process_wait(void)
{
	pid_t pid_z;
	//循环清除节点
	while(pid_z=wait(NULL)!=-1)
	{
		printf("delete process running.....\n");
	}
}
