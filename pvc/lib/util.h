#ifndef COMMON
#define COMMON
#include "common.h"
#endif
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

void map_file(const char * filename, void * & buf, unsigned int & size){
	int fp=open(filename,O_RDONLY);
	if(fp){
		struct stat filestat;
		fstat(fp, &filestat);
		size=filestat.st_size;
		buf=mmap(0,size,PROT_READ,MAP_PRIVATE,fp,0);
	}
	else
	buf=0;
}

double rtclock() //return the clock
{
	struct timezone Tzp;
	struct timeval Tp;
	int stat;
	stat = gettimeofday (&Tp, &Tzp);
	if (stat != 0) printf("Error return from gettimeofday: %d",stat);
	return(Tp.tv_sec + Tp.tv_usec*1.0e-6);
};

__device__ void copyVal(void *dst, void *src, unsigned short size)
{
	 char *d=(char*)dst;
	 const char *s=(const char *)src;
	 for(unsigned short i=0;i < size;i++)
		 d[i]=s[i];
}


__device__ unsigned int align(unsigned int size)
{
	return (size+ALIGN_SIZE-1)&(~(ALIGN_SIZE-1));
}
