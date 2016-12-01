#include<stdio.h>
#include<stdlib.h>


void main(void)
{

char a[2]={'a','b'};
char* b;

b=a;
b[0]='c';
b[1]='c';

printf("%c %c\n",a[0],a[1]);

}
