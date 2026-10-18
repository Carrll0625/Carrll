#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
//定义函数
int check_pram(int ,const char* , int );//参数验证
int block_cur(const char* ,int );//切片
int process_create(const char* ,const char* ,int ,int );//创建进程
int process_wait(void);
