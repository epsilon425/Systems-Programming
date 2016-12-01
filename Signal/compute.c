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

	void terminator();	
	int sid;
	struct memConstruct *sharedMem;
	
	signal(SIGINT, terminator);
	signal(SIGHUP, terminator);
	signal(SIGQUIT, terminator);
	
		
	sid=shmget(KEY_MM,sizeof(struct memConstruct),IPC_CREAT|0666);

        sharedMem=((struct memConstruct*)shmat(sid,0,0));

	int qid;
	int input = atoi(argv[1]);
	qid = msgget(KEY_MQ,IPC_CREAT | 0666);
	
	while(1)
	{

		if(!(sharedMem->bits[input/32]&(1<<(input%32))))
		{	
			int i,sum;
			sum=1;	
			for(i=2;i<input;i++)
				if(!(input%i)) sum+=i;
			if(sum==input)//if pnum is found 
			{
				my_msg.type=1;
				my_msg.data[0]=getpid();		
				my_msg.data[1]=input;
				msgsnd(qid,&my_msg,sizeof(my_msg.data),0);
				input++;
				continue;
			}
	
			my_msg.type = 2;
			my_msg.data[0]=getpid();
			my_msg.data[1]=input;
			msgsnd(qid,&my_msg,sizeof(my_msg.data),0);
			input++;
			continue;
		}
		my_msg.type=3;
		my_msg.data[0]=getpid();
		my_msg.data[1]=input;
		msgsnd(qid,&my_msg,sizeof(my_msg.data),0);			
		input++;
	}

}

void terminator()
{
int i=0;
struct memConstruct *sharedMem;
int sid = shmget(KEY_MM,sizeof(struct memConstruct),IPC_CREAT|0666);
sharedMem = (struct memConstruct*)shmat(sid,0,0);
for(i=0;i<20;i++)
{
	proX temp = sharedMem->processes[i];
	if(temp.pid==getpid())
	{

		temp.pid=0;
		temp.pfound=0;
		temp.tested=0;
		temp.ntested=0;
		sharedMem->processes[i]=temp;
	
	}

}

exit(EXIT_SUCCESS);
}

