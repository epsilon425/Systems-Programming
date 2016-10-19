/*
 THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING

A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Paul Ahn 
*/
#include <stdio.h>
#include <stdlib.h>

#define BITSPERSEG (8*256*sizeof(int))

typedef struct seg
{

	int bits[256];
	struct seg *next,*prev;

}seg;
seg *head, *pt;
//whichseg:(j-3)/16384
//whichint: ((j-3)%16384)/64
//whichbit: ((j-3)/2)%32
int whichint(int j)
{
return(((j-3)%16384)/64);

}

int whichbit(int j)
{

int x = ((j-3)/2)%32;
return x;
}

seg* whichseg(int j)
{

static seg *lastseg;
static int lastj=0;
if(lastseg==NULL)lastseg = head;
seg *x = head;
int y = (j-3)/16384;
if(j>lastj) 
{
y= y-((lastj-3)/16384);
x= lastseg;
}		
for(int i=0;i<y;i++)
{
x = x->next;

}
lastseg = x;
lastj=j;

return x;
}

int testbit(int j,int q, seg *k)
{

int x = j;
int y = q;
seg *z = k;
return( (z->bits[x]&(1<<y))==0);
}

int marknoprime (int j)
{
int x = whichint(j);
int y = whichbit(j);
seg *z = whichseg(j);

if(testbit(x,y,z))
{
z->bits[x] |= 1<< y;
}

}

void main (int argc, char *argv[])
{
int input;
int number;
if(argc==2) sscanf(argv[1],"%d",&input);
	else return;
number = input;
input = (input+((BITSPERSEG)-1))/(2*BITSPERSEG);

head = (seg*)malloc(sizeof(seg));
pt = head;

seg* temp = (seg*)malloc(sizeof(seg));

for(int i=0;i<input;i++)
{
temp = pt;
pt->next = (seg*)malloc(sizeof(seg));
pt = pt->next;
pt->prev = temp;
}
//===================================================================Memory Allocated
for(int i=3;i<=number;i=i+2)
{
	for(int j=2;i*j<=number;j++)
	{

		if(((i*j)%2)!=0)
		{		
		marknoprime(i*j);
		}
	}	
		
		
}
//The bit representing non-prime odd number has been marked 

int count=0;
for(int i=3;i<=number;i=i+2)
	{
	
	int x=whichint(i);
	int y=whichbit(i);
	seg*z=whichseg(i);
	if(testbit(x,y,z)) 
		{ 	  
   		  count++;
		}
	}
printf("Calculating odd primes up to %d\n",number);
printf("Found %d odd primes \n",count);
//Counted and checked all the odd prime numbers. 
//===============================================================================================
//goldbach begins
int goldNUM;
printf("Enter Even Numbers >5 for Goldbach Tests: ");

while( scanf("%d",&goldNUM) != EOF )
{
if((goldNUM%2)!=0)
{
printf("Please enter an even number \n");
continue;
}
int bgnINT=whichint(3);
int bgnBIT=whichbit(3);
seg*bgnSEG=whichseg(3);

int endINT=whichint(goldNUM-3);
int endBIT=whichbit(goldNUM-3);
seg*endSEG=whichseg(goldNUM-3);
int counter=0;
int biggy=0;
for(int i=3;i<=(goldNUM/2);i=i+2)
	{
		if(testbit(bgnINT,bgnBIT,bgnSEG)&testbit(endINT,endBIT,endSEG))
		{
			if(i>biggy) biggy=i;
			counter++;
		}
		bgnBIT++;
		endBIT--;
		if(bgnBIT>31)
			{
			bgnBIT=0;
			bgnINT++;
			}

		if(endBIT<0)	
			{
			endBIT=31;
			endINT--;
			}	
	
		if(bgnINT>255)
			{
			bgnINT=0;
			bgnSEG = bgnSEG->next;			
			}
		if(endINT<0)
			{
			endINT=255;
			endSEG = endSEG->prev;
			}
	}


printf("The Largest %d = %d + %d out of %d solutions\n",goldNUM,biggy,goldNUM-biggy,counter);
}
}
