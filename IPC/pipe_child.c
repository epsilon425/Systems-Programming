#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
int pipefd[2];
pid_t cpid;
char buf;
char* fixarg = malloc(15*sizeof(char));

printf("Parents PID: %d\n",getpid());
begin:

if (argc != 2)
	{
	printf("%s","Input what you want your child to get: ");
	scanf("%s",fixarg);	
	}

if (pipe(pipefd)==-1)
	{	
	printf("%s\n","The pipe was not initialized correctly");
	return 0;
	}

cpid = fork();
if (cpid==-1)
	{
	printf("%s\n","The fork process was not handled correctly");
	return 0; 
	}

if(cpid==0)
	{
	printf("Child's PID:%d\n",getpid());
	close(pipefd[1]); //close unused write end because child get the data
	while(read(pipefd[0]/*read end of pipe */,&buf,1) > 0)
		{
		write(STDOUT_FILENO, &buf, 1);//write to standard out buffer
		}
	write(STDOUT_FILENO,"\n",1);
	close(pipefd[0]);//closes the read end to signify the ending
	}

else 
	{
	close(pipefd[0]); //close the read side of the pipe
	if(strcmp(fixarg,"")==0) write(pipefd[1], argv[1], strlen(argv[1]));
		else write(pipefd[1], fixarg, strlen(fixarg));
	close(pipefd[1]);
	wait(NULL);	
	}

}
