#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
int pipefd[2];
int parid;
int i=0;
char theChar;
int  numChar;
FILE *stdoutF;
if(pipe(pipefd)==-1) printf("%s\n","Pipe was not initialized correctly");
parid = fork();

if(parid==0)
{
close(pipefd[1]);

}
else
{
close(pipefd[0]);
stdoutF = fdopen(STDIN_FILENO, "r");
while(feof(stdoutF)==0)
{	

	theChar=fgetc(stdoutF);
	numChar=(int)theChar;
	while((numChar>64&&numchar<123)
	{
		 
		if(numChar>64&&numChar<91)
		{
		
		numChar=numChar-32;
	 	theChar=(char)numChar;

		}

		buffer[i]=theChar;
		i++;

	}

}
}

}
