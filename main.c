#include "ncx_slab.h"

int main(int argc, char **argv)
{
	char *p;
	size_t 	pool_size = 4096000;  //4M 
	ncx_slab_stat_t stat;
	u_char 	*space;
	space = (u_char *)malloc(pool_size);

	ncx_slab_pool_t *sp;
	sp = (ncx_slab_pool_t*) space;

	sp->addr = space;
	sp->min_shift = 3;
	sp->end = space + pool_size;

	ncx_slab_init(sp);

	int i;
	for (i = 0; i < 1000000; i++) 
	{   
		p = ncx_slab_alloc(sp, 128 + i); 
		if (p == NULL) 
		{   
			printf("%d\n", i); 
			return -1; 
		}   
		ncx_slab_free(sp, p); 
	}   
	ncx_slab_stat(sp, &stat);

	printf("##########################################################################\n");
	for (i = 0; i < 2500; i++) 
	{   
		p = ncx_slab_alloc(sp, 30 + i); 
		if (p == NULL) 
		{   
			printf("%d\n", i); 
			return -1; 
		}   
		
		if (i % 3 == 0) 
		{
			ncx_slab_free(sp, p);
		}
	}   
	ncx_slab_stat(sp, &stat);

	free(space);

	return 0;
}
