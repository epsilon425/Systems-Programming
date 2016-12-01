/* 
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING

A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Paul Ahn  
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void main (void)
{
int pipefd[2];
int pipe2fd[2];
char theChar;
char theChar2=2;
char newL='\n';
int N=0;
int count=0;
int wordcount=1;
FILE *stdinF;
FILE *PIPE1;
FILE *PIPE2;
char buffer[31];
char temp[31];
int one=0;

if(pipe(pipefd)==-1)
{

	printf("%s","Pipe was not initialized correctly");
	return;
}

if(pipe(pipe2fd)==-1)
{

	printf("%s","Pipe was not initialized correctly");
	return;

}

if(fork()==0) //parent->child
	{
	close(pipe2fd[0]);
	close(pipefd[1]);

	dup2(pipefd[0],STDIN_FILENO);//connect the input of pipe to stdin 
	dup2(pipe2fd[1],STDOUT_FILENO);//connect the output to the second child
	
	close(pipefd[0]);//close because already dudped to stdin 
	close(pipe2fd[1]);
	execl("/usr/bin/sort","/usr/bin/sort","-b",(char*)NULL);//execute sort
	printf("%s\n","Something wrong with execution");
		
	
	}

if(fork()==0)//-->second child;suppresses and counts
	{
	close(pipefd[0]);
	close(pipefd[1]);
	close(pipe2fd[1]);
	PIPE2=fdopen(pipe2fd[0],"r");
	while(theChar!=EOF)
	{
		int i=0;
		theChar=fgetc(PIPE2);

		if(theChar==EOF)
		{

			printf("%5d %s\n",wordcount,temp);
			return;
		}
		while(theChar!='\n')
		{

			buffer[i]=theChar;
			theChar=fgetc(PIPE2);
			i++;
		
		}

		if(i<3)
		{
			memset(&buffer[0],0,30);
			continue;
		}

		if(one==0)
		{
			strncpy(temp,buffer,i);
			one++;
			continue;
		}
		//printf("%s\n",buffer);
		
		if(!strcmp(temp,buffer))
		{

			wordcount++;

		}

		if(strcmp(temp,buffer))	
		{
			printf("%5d %s\n",wordcount, temp);
			memset(&temp[0],0,30);
			strcpy(temp,buffer);
			wordcount=1;
		}
		memset(&buffer[0],0,30);
	}
		close(pipe2fd[0]);
	}
else //parent 
	{
	close(pipefd[0]);
	close(pipe2fd[0]);
	close(pipe2fd[1]);
	stdinF = fdopen(STDIN_FILENO,"r");
	PIPE1 = fdopen(pipefd[1],"w");
	
	while(theChar!=EOF)
		{
		theChar=fgetc(stdinF);
		if(count==30)
			{
			count=0;
			while(isalpha(theChar))
				{
				
					theChar=fgetc(stdinF);
					
				}
			}
		if(!isalpha(theChar)&&N==0)
			{
			count=0;
			N++;
			fputc(newL,PIPE1);
			}
		if(isalpha(theChar))
			{
			N=0;
			count++;
			theChar=tolower(theChar);
			fputc(theChar,PIPE1);
			}
		}
		fclose(PIPE1);
		close(pipefd[1]);
		wait(NULL);	
		wait(NULL);


		}


	}
