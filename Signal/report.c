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

#define KEY_MQ (key_t) 425425
#define KEY_MM (key_t) 123412
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


void main(int argc, char* argv[])
{	
	int sid;
	struct memConstruct *sharedMem;
	
	sid=shmget(KEY_MM,sizeof(struct memConstruct),IPC_CREAT|0666);
	sharedMem=((struct memConstruct*)shmat(sid,0,0));	
	if(argc==2)
		if(strcmp("-k",argv[1])==0)
		{
			int mpid = sharedMem->managerpid;
			kill(mpid,SIGINT);			
		}
	printf("tested: %d, skipped: %d, found: %d\n",sharedMem->sumtested,sharedMem->sumntested,sharedMem->sumpfound);

	int i=0;
	for(i=0;i<20;i++)
	{
		proX temp = sharedMem->processes[i];

		printf("PID: %d tested: %d  skipped: %d  found: %d\n",temp.pid,temp.tested,temp.ntested,temp.pfound);

	}		
}
