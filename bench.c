#include "ncx_slab.h"
#include <sys/time.h>

uint64_t usTime()  
{
	struct timeval tv;
	uint64_t usec;

	gettimeofday(&tv, NULL);

	usec = ((uint64_t)tv.tv_sec)*1000000LL;
	usec += tv.tv_usec;

	return usec;
}

int main(int argc, char **argv)
{
	ncx_slab_pool_t *sp;
	size_t 	pool_size;
	u_char 	*space;
	   
	pool_size = 4096000;  //4M 
	space = (u_char *)malloc(pool_size);
	sp = (ncx_slab_pool_t*) space;

	sp->addr = space;
	sp->min_shift = 3;
	sp->end = space + pool_size;

	ncx_slab_init(sp);

	char *p;
	uint64_t us_begin;
	uint64_t us_end;
	size_t size[] = { 30, 120, 256, 500, 1000, 2000, 3000, 5000};

	printf("size\tncx\tmalloc\n");

	int i, j;
	for (j = 0; j < sizeof(size)/sizeof(size_t); j++) 
	{
		size_t s = size[j];
		printf("%d\t", s);

		//test for ncx_pool
		us_begin  = usTime();
		for(i = 0; i < 1000000; i++) 
		{
			p = ncx_slab_alloc(sp, s);
			ncx_slab_free(sp, p);
		}
		us_end  = usTime();

		printf("%llu \t", (us_end - us_begin)/1000);

		// test for malloc
		us_begin  = usTime();
		for(i = 0; i < 1000000; i++) 
		{
			p = (char*)malloc(s);
			free(p);
		}
		us_end  = usTime();

		printf("%llu\n", (us_end - us_begin)/1000);
	}

		
	free(space);

	return 0;
}
