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

	/*
	 * init
	 */
	ncx_slab_init(sp);

	/*
	 * alloc
	 */
	p = ncx_slab_alloc(sp, 128);

	/*
	 * show stat
	 */
	ncx_slab_stat(sp, &stat);

	/*
	 * free
	 */
	ncx_slab_free(sp, p);

	free(space);

	return 0;
}
