/* 
All of optional commands d,v has been implemented.
Support for mutiple file is still on the way
*/
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/cdefs.h>
#include <ar.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define ARMAG	"!<arch>\n"	/* String that begins an archive file.  */
#define SARMAG	8		/* Size of that string.  */
#define ARFMAG	"`\n"		/* String in ar_fmag at end of each header.  */
struct dirent mydirect;
struct ar_hdr myheader;
struct stat archivestat;
struct stat filestat;
struct timeval mytime; 
//====================================================================================T_FUNC
void t_function(char archivename[])
{
int archivefd= open(archivename,0);
fstat(archivefd, &archivestat);
lseek(archivefd,8,SEEK_SET);
int filesize=0;
int archivesize=archivestat.st_size-8;
while(425)
	{
	char* filename=(char*)malloc(sizeof(myheader.ar_name));	
	struct ar_hdr myheader;
	read(archivefd, &myheader, 60);
	archivesize = archivesize-60;	
	sscanf(myheader.ar_size,"%d",&filesize);
	if(filesize%2!=0) filesize = filesize+1;	
	archivesize=archivesize-filesize;
	sscanf(myheader.ar_name,"%s",filename);
	int i=0;	
	
	for(i=0;i<sizeof(filename);i++)
	{
		if(filename[i]=='/') filename[i]=' ';
	}
	printf("%s\n",filename);	
	lseek(archivefd,filesize,SEEK_CUR);
	if(archivesize==0) return;	
	}
}
//====================================================================================X_FUNC
void x_function(char archivename[], char file[])
{
int fd;
int archivefd= open(archivename,0);
int filefd   = open(file   ,0);
long mtime;
unsigned int mmode;
fstat(archivefd, &archivestat);
fstat(filefd   , &filestat   );
lseek(archivefd,8,SEEK_SET);
int filesize=0;
int archivesize=archivestat.st_size-8;
char* filebuf;
int count = strlen(file);
while(425)
	{	
	char* filename = (char*)malloc(sizeof(myheader.ar_name));
	struct ar_hdr myheader;
	read(archivefd, &myheader, 60);
	archivesize = archivesize-60;
	sscanf(myheader.ar_size,"%d",&filesize);
	if(filesize%2!=0) filesize = filesize+1;
	sscanf(myheader.ar_name,"%s",filename);	
	int i=0;
	for(i=0;i<sizeof(filename);i++)
	{
		if(filename[i]=='/') filename[i]=' ';
	}
		
	if(strncmp(filename,file,count)==0)
		{
		//printf("%s\n",myheader.ar_date);
		//printf("%s\n",myheader.ar_mode);
		sscanf(myheader.ar_date,"%ld",&mtime);
		sscanf(myheader.ar_mode,"%d",&mmode);		
		filebuf = (char*)malloc(filesize);
		read(archivefd,filebuf,filesize);
		break;		
		}
	lseek(archivefd,filesize,SEEK_CUR); 
	archivesize = archivesize-filesize;	
	if(archivesize<0) 
		{
		printf("Wrong input, file does not exist in archive\n");
		return;	
		}	
	}

mytime.tv_sec=mtime;
mytime.tv_usec=mtime;

int newfd = creat(file,0666);
write(newfd, filebuf,filesize);
utimes(file,&mytime);
umask(mmode);
close(newfd);
struct stat test;
stat(file,&test);
//printf("%ld\n",test.st_mtime);
//printf("%d\n",test.st_mode);
}
//======================================================================================V_FUNC
void v_function(char archivename[])
{
int archivefd = open(archivename,0);
fstat(archivefd,&archivestat);
lseek(archivefd,8,SEEK_SET);
int filesize = 0;
int archivesize = archivestat.st_size-8;
long mode;
while(425)
	{
	char* filename=(char*)malloc(sizeof(myheader.ar_name));	
	char* filemode=(char*)malloc(sizeof(myheader.ar_mode));
	char* timestam=(char*)malloc(sizeof(myheader.ar_date));
	char* fileuid =(char*)malloc(sizeof(myheader.ar_uid ));
	char* filegid =(char*)malloc(sizeof(myheader.ar_gid ));
	char* cfilesize=(char*)malloc(sizeof(myheader.ar_size));
	struct ar_hdr myheader;
	read(archivefd, &myheader, 60);
	archivesize = archivesize-60;	
	sscanf(myheader.ar_size,"%d",&filesize);
	if(filesize%2!=0) filesize = filesize+1;	
	archivesize=archivesize-filesize;
	sscanf(myheader.ar_name,"%s",filename);
	int i=0;	
	
	for(i=0;i<sizeof(filename);i++)
	{
		if(filename[i]=='/') filename[i]=' ';
	}
	sscanf(myheader.ar_mode,"%s",filemode);
	sscanf(myheader.ar_date,"%s",timestam);
	sscanf(myheader.ar_uid ,"%s",fileuid);
	sscanf(myheader.ar_gid ,"%s",filegid);
	sscanf(myheader.ar_size,"%s",cfilesize);
	lseek(archivefd,filesize,SEEK_CUR);
	printf("%s %s/%s %s %s %s\n", filemode, fileuid,filegid,timestam, cfilesize,filename); 
	if(archivesize==0) return;	
	}
}

//=====================================================================================================================================================Q_FUNC
void q_function(char archivename[], char filename[])
{
if(open(filename,0)==-1)
	{

	printf("Wrong file name\n");
	return;

	}

int filefd = open(filename,0666);
fstat(filefd,&filestat);

long BLOCKSIZE=filestat.st_blksize;
long FILESIZE=filestat.st_size;
int blocks = FILESIZE/BLOCKSIZE;
int remainbyte = FILESIZE%BLOCKSIZE;
char* headbuffer = (char*)malloc(61);
strcat(filename,"/");
sprintf(headbuffer,"%-16s%-12ld%-6d%-6d%-8d%-10ld%-2s",filename,filestat.st_mtime,filestat.st_uid,filestat.st_gid,filestat.st_mode,filestat.st_size,ARFMAG);

int i=0;
while(headbuffer[i]!=' ')i++;
headbuffer[i]=='/';
int fdtemp = open(archivename,000);


if(fdtemp==-1)
{
close(fdtemp);
int newfd = creat(archivename,0666);
write(newfd,ARMAG,SARMAG);
write(newfd,headbuffer,60);
while(blocks>0)
	{
		char* buffer = (char*) malloc(filestat.st_blksize);
		read(filefd,&buffer,sizeof(buffer));
		write(newfd,&buffer,sizeof(buffer));
		
	}
if(remainbyte!=0)
	{
		char* buffer = (char*) malloc(filestat.st_blksize);
		read(filefd,&buffer,remainbyte);
		write(newfd,&buffer,remainbyte);
	}
if(filestat.st_size%2!=0)
	write(newfd,"\n",1);
}

else
{
int archivefd= open(archivename,0666);
fstat(archivefd, &archivestat);
lseek(archivefd,0,SEEK_END);
write(archivefd,headbuffer,60);
while(blocks>0)
	{
		char* buffer = (char*) malloc(filestat.st_blksize);
		read(filefd,&buffer,sizeof(buffer));
		write(archivefd,&buffer,sizeof(buffer));
		
	}
if(remainbyte!=0)
	{
		char* buffer = (char*) malloc(filestat.st_blksize);
		read(filefd,&buffer,remainbyte);
		write(archivefd,&buffer,remainbyte);	
	}
if(filestat.st_size%2!=0)
	write(archivefd,"\n",1);
}

}
//=========================================================================================================================A_FUNC
void a_function(char archive[])
{  

DIR *dp;
struct dirent *ep;
char dirfilename[15];
  
dp = opendir ("./");
int i=0;
if (dp != NULL)
    {
      while (ep = readdir (dp))
	{
        
		if(ep->d_name[0]!='.')
	   {        
		sprintf(dirfilename,"%s",(ep->d_name));
 		   if(strcmp(archive,dirfilename)!=0)
		   {	
		   stat(dirfilename,&filestat);	
		   long tpassed;
        	   time(&tpassed);
		   long tdiff = tpassed - filestat.st_mtime;
		   if(1<=(tdiff/3600)) q_function(archive,dirfilename);	
		   }
	   }
	}	
      (void) closedir (dp);
    
	}

}
//================================================================================================================================================D_FUNC
void d_function(char archivename[], char file[])
{
int fd;
int archivefd= open(archivename,0);
int filefd   = open(file   ,0);

fstat(archivefd, &archivestat);
fstat(filefd   , &filestat   );
lseek(archivefd,8,SEEK_SET);
int filesize=0;
int archivesize=archivestat.st_size-8;
char* filebuf;
int count = strlen(file);
char* filenameF=(char*)malloc(sizeof(myheader.ar_name));
while(425)      
        {       
        char* filename = (char*)malloc(sizeof(myheader.ar_name));
        struct ar_hdr myheader;
        read(archivefd, &myheader, 60);
        archivesize = archivesize-60;
        sscanf(myheader.ar_size,"%d",&filesize);
        if(filesize%2!=0) filesize = filesize+1;
        sscanf(myheader.ar_name,"%s",filename);
        int i=0;
        for(i=0;i<sizeof(filename);i++)
        {
                if(filename[i]=='/') filename[i]=' ';
        }       
                
        if(strncmp(filename,file,count)==0)
                {
		filenameF=filename;
                break;
                }
        lseek(archivefd,filesize,SEEK_CUR);
        archivesize = archivesize-filesize;
        if(archivesize<0)
                {
                printf("Wrong input, file does not exist in archive\n");
                return;
                }
        } 


int prearchivesize = archivestat.st_size-60-filesize;
archivesize = archivesize-filesize;

filebuf=(char*)malloc(prearchivesize);

lseek(archivefd,0,SEEK_SET);
//creat(archivename,0666);
read(archivefd,filebuf,prearchivesize);
lseek(archivefd,filesize+60,SEEK_CUR);
read(archivefd,filebuf,archivesize);
unlink(archivename);
int newarchivefd=creat(archivename,0666);
write(newarchivefd,filebuf,prearchivesize);
close(archivefd);
}
		
			

//===================================================================================================================end of functions

void main(int argc, char* argv[])
{
//t_function(argv[1]);
//x_function(argv[1],argv[2]);
//v_function(argv[1]);
//q_function(argv[1], argv[2]);
//a_function(argv[1]);
//d_function(argv[1],argv[2]);
//argc includes the ./a.out
if(argc==3)
{
if(*argv[1]=='t') t_function(argv[2]);
if(*argv[1]=='v') v_function(argv[2]);
if(*argv[1]=='a') a_function(argv[2]);
}

if(argc==4)
{
if(*argv[1]=='x') x_function(argv[2],argv[3]);
if(*argv[1]=='q') 
{
printf("%s\n","entering q");
q_function(argv[2],argv[3]);
}
if(*argv[1]=='d') d_function(argv[2],argv[3]);
}

}	
