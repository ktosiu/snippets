#include<time.h>
#include<stdio.h>
int main()
{
	long seconds= time((time_t*)NULL);
	printf("%ld\n",seconds);
	return 0;
}
