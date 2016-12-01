#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#define KEY_MQ (key_t) 425425        /*key for message queue */
#define KEY_MM (key_t) 123412

int theEnd=0;

struct
{
long type;
int data[2];
}my_msg;

typedef struct process
{
        int pid;
        int pfound;
        int tested;
        int ntested;
}proX;

struct memConstruct
{
        int bits[1048576];
        int pfound[20];
        proX processes[20];
        int sumpfound;
        int sumtested;
        int sumntested;
	int managerpid;
};
struct memConstruct *final;
int finalQ=0;
void main(int argc, char* argv[])
{
	int sid;
	struct memConstruct *sharedMem;
	void terminator();
	signal(SIGINT, terminator);
	signal(SIGHUP, terminator);
	signal(SIGQUIT, terminator);	
	sid=shmget(KEY_MM,sizeof(struct memConstruct),IPC_CREAT |0666);
	sharedMem=(struct memConstruct *) shmat(sid,0,0);
	final = sharedMem;
	sharedMem->managerpid=getpid();
	int qid;
	qid = msgget(KEY_MQ,IPC_CREAT | 0666);
	finalQ=qid;
	int cprocess=0;
	while(1)
	{
		start:
		if((msgrcv(qid,&my_msg,sizeof(my_msg.data),1,IPC_NOWAIT))!=-1)
		{
			int i=0;
			int pid = my_msg.data[0];
			int number = my_msg.data[1];

			sharedMem->bits[number/32]|=(1<<(number%32));
			if(cprocess==0)
			{
				sharedMem->sumpfound=1;
				sharedMem->sumtested=1;
				sharedMem->sumntested=0;
				proX temp;
				temp.pid = my_msg.data[0];
				temp.pfound = 1;
				temp.tested = 1;
				temp.ntested= 0;
				sharedMem->processes[cprocess]=temp;
				cprocess++;
				continue;
			}
			
			for(i=0;i<20;i++)
			{
				proX temp = sharedMem->processes[i];
				if(temp.pid==my_msg.data[0])
				{
					sharedMem->sumpfound++;
					sharedMem->sumtested++;
					temp.pfound++;
					temp.tested++;
					sharedMem->processes[i]=temp;
					goto start;
				}


			}

			sharedMem->sumpfound++;
			sharedMem->sumtested++;
			proX temp;
			temp.pid = my_msg.data[0];
			temp.pfound=1;
			temp.tested=1;
			temp.ntested=0;
			sharedMem->processes[cprocess]=temp;
			cprocess++;
	

		}


		else if((msgrcv(qid,&my_msg,sizeof(my_msg.data),2,IPC_NOWAIT))!=-1)
		{
			int i=0;
			int number = my_msg.data[1];
			sharedMem->bits[number/32]|=(1<<(number%32));

			if(cprocess==0)
			{
				sharedMem->sumpfound=0;
				sharedMem->sumtested=1;
				sharedMem->sumntested=0;
				proX temp;
				temp.pid = my_msg.data[0];
				temp.pfound = 0;
				temp.tested = 1;
				temp.ntested= 0;
				sharedMem->processes[cprocess]=temp;
				cprocess++;
				continue;
			}
		
			for(i=0;i<20;i++)
			{
				proX temp = sharedMem->processes[i];
				if(temp.pid==my_msg.data[0])
				{
					sharedMem->sumtested++;
					temp.tested++;
					sharedMem->processes[i]=temp;
					goto start;
				}

			
			}
			
			sharedMem->sumtested++;
			proX temp;
			temp.pid = my_msg.data[0];
			temp.pfound = 0;
			temp.tested = 1;
			temp.ntested= 0;
			sharedMem -> processes[cprocess]=temp;
			cprocess++;
			
		}

	
		else if((msgrcv(qid,&my_msg,sizeof(my_msg.data),3,IPC_NOWAIT))!=-1)
		{
			int i=0;
			if(cprocess==0)
			{
				sharedMem->sumpfound=0;
				sharedMem->sumtested=0;
				sharedMem->sumntested=1;
				proX temp;
				temp.pid = my_msg.data[0];
				temp.pfound = 0;
				temp.tested = 0;
				temp.ntested= 1;
				sharedMem->processes[cprocess]=temp;
				cprocess++;
				continue;
			}
			
			for(i=0;i<20;i++)
			{
				proX temp = sharedMem->processes[i];
				if(temp.pid==my_msg.data[0])
				{
					sharedMem->sumntested++;
					temp.ntested++;
					sharedMem->processes[i]=temp;
					goto start;
				}	

			}
		
			sharedMem -> sumntested++;
			proX temp;
			temp.pid = my_msg.data[0];
			temp.pfound =0;
			temp.tested=0;
			temp.ntested=1;
			sharedMem->processes[cprocess]=temp;
			cprocess++;
		}
	}
}

void terminator()
{
	int sid=shmget(KEY_MM,sizeof(struct memConstruct),IPC_CREAT|0666);

	int i=0;

	for(i=0;i<20;i++)
	{

		proX temp = final->processes[i];
		kill(temp.pid,SIGINT);	
	}

	sleep(5);
	
	msgctl(finalQ,IPC_RMID,0);
	shmdt((struct memConstruct*)final);
	shmctl(sid,IPC_RMID,0);		
	exit(EXIT_SUCCESS);
}	
