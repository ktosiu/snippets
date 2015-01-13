#include<time.h>
#include<stdio.h>
int main()
{
	time_t timep;
	time (&timep);
	printf("%s",ctime(&timep));
	return 0;
} 
