#ifndef _NCX_SLAB_H_INCLUDED_
#define _NCX_SLAB_H_INCLUDED_


#include "ncx_core.h"
#include "ncx_lock.h"
#include "ncx_log.h"

typedef struct ncx_slab_page_s  ncx_slab_page_t;

struct ncx_slab_page_s {
    uintptr_t         slab;
    ncx_slab_page_t  *next;
    uintptr_t         prev;
};


typedef struct {
    size_t            min_size;
    size_t            min_shift;

    ncx_slab_page_t  *pages;
    ncx_slab_page_t   free;

    u_char           *start;
    u_char           *end;

	ncx_shmtx_t		 mutex;

    void             *addr;
} ncx_slab_pool_t;

typedef struct {
	size_t 			pool_size, used_size, used_pct; 
	size_t			pages, free_page;
	size_t			p_small, p_exact, p_big, p_page; /* 四种slab占用的page数 */
	size_t			b_small, b_exact, b_big, b_page; /* 四种slab占用的byte数 */
	size_t			max_free_pages;					 /* 最大的连续可用page数 */
} ncx_slab_stat_t;

void ncx_slab_init(ncx_slab_pool_t *pool);
void *ncx_slab_alloc(ncx_slab_pool_t *pool, size_t size);
void *ncx_slab_alloc_locked(ncx_slab_pool_t *pool, size_t size);
void ncx_slab_free(ncx_slab_pool_t *pool, void *p);
void ncx_slab_free_locked(ncx_slab_pool_t *pool, void *p);

void ncx_slab_dummy_init(ncx_slab_pool_t *pool);
void ncx_slab_stat(ncx_slab_pool_t *pool, ncx_slab_stat_t *stat);

#endif /* _NCX_SLAB_H_INCLUDED_ */
