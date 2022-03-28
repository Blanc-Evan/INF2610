
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
int x=0; 
int main() { 
   x=x+1;
   int pid=fork();  
   x=(x+2)*pid;
   if (pid!=0) { x=x+2; wait(0); exit(0); } 
   else x=x+2; 
   printf("x=%d\n",x); 
   return 0;
  } 