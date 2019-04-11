/*
* mm-naive.c - The fastest, least memory-efficient malloc package.
* POVIS ID : andrea0119
* In this naive approach, a block is allocated by simply incrementing
* the brk pointer.  A block is pure payload. There are no headers or
* footers.  Blocks are never coalesced or reused. Realloc is
* implemented directly using mm_malloc and mm_free.
*
* NOTE TO STUDENTS: Replace this header comment with your own header
* comment that gives a high level description of your solution.
*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "memlib.h"
#include "mm.h"
/*********************************************************
* NOTE TO STUDENTS: Before you do anything else, please
* provide your team information in the following struct.
********************************************************/
team_t team = {
	/* Team name */
	"ateam",
	/* First member's full name */
	"Harry Bovik",
	/* First member's email address */
	"bovik@cs.cmu.edu",
	/* Second member's full name (leave blank if none) */
	"",
	/* Second member's email address (leave blank if none) */
	""
};

//word������� ���� �þ ûũ������ ����
#define WSIZE      sizeof(void *) 
#define DSIZE      (2 * WSIZE)    
#define CHUNKSIZE  (1 << 12)      

#define MAX(x, y) ((x) > (y) ? (x) : (y))

//PACK���� allocate�� ������ size����
#define PACK(size, alloc)  ((size) | (alloc))

//get�� put���� Ư���ּҿ� �ִ� ���� read/write����
#define GET(p)       (*(uintptr_t *)(p))
#define PUT(p, val)  (*(uintptr_t *)(p) = (val))

//size�� allocate�� ������ read
#define GET_SIZE(p)   (GET(p) & ~(DSIZE - 1))
#define GET_ALLOC(p)  (GET(p) & 0x1)
//adress�󿡼� block�� header��footer
#define HDRP(bp)  ((void *)(bp) - WSIZE)
#define FTRP(bp)  ((void *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

//next�� prev���� ���� ������
#define NEXT_BLK(bp)  ((void *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLK(bp)  ((void *)(bp) - GET_SIZE((void *)(bp) - DSIZE))

//next�� prev����� ������ get�ϴ� ��
#define GET_NEXT_PTR(bp)  (*(char **)(bp + WSIZE))
#define GET_PREV_PTR(bp)  (*(char **)(bp))

//next�� prev��带 ���������ִ� ��
#define SET_NEXT_PTR(bp, qp) (GET_NEXT_PTR(bp) = qp)
#define SET_PREV_PTR(bp, qp) (GET_PREV_PTR(bp) = qp)

//globcl ������
static char *heap_listp = 0;
static char *free_list_start = 0;

static void *coalesce(void *bp);
static void *extend_heap(size_t words);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);
static void node_insert(void *bp);
static void node_remove(void *bp);

/*
* mm_init - initialize the malloc package.
*/
int mm_init(void) {

	//ó���� ���� ������Ų��.
	if ((heap_listp = mem_sbrk(8 * WSIZE)) == NULL)
		return -1;

	//padding���� �Ŀ� header�� footer�� ����
	PUT(heap_listp, 0);                            
	PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); 
	PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1)); 
	PUT(heap_listp + (3 * WSIZE), PACK(0, 1));     
	free_list_start = heap_listp + 2 * WSIZE;

	//heap�� �ּ��� ũ��� �䱸�ϴ¸�ŭ extend
	if (extend_heap(4) == NULL) {
		return -1;
	}
	return 0;
}

/*
* mm_malloc - Allocate a block by incrementing the brk pointer.
*     Always allocate a block whose size is a multiple of the alignment.
*/
void *mm_malloc(size_t size)
{
	size_t asize;      
	size_t extendsize; 
	void *bp;

	//����ó��
	if (size == 0)
		return (NULL);

	//block size�� ���� heap�� �������θ� ����
	if (size <= DSIZE)
		asize = 2 * DSIZE;
	else
		asize = DSIZE * ((size + DSIZE + (DSIZE - 1)) / DSIZE);

	//heap�������Ұ��� üũ
	if ((bp = find_fit(asize)) != NULL) {
		place(bp, asize);
		return (bp);
	}

	//���࿡ extend�ؾ��� ��� heap���ٰ� ����
	extendsize = MAX(asize, CHUNKSIZE);
	if ((bp = extend_heap(extendsize / WSIZE)) == NULL)
		return (NULL);
	place(bp, asize);
	return (bp);
}

/*
* mm_free - Freeing a block does nothing.
*/
void mm_free(void *bp) {
	size_t size;
	//����ó��
	if (bp == NULL)
		return;
	//�����ŭ�������ְ� �յ����� ��ħ
	size = GET_SIZE(HDRP(bp));
	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	coalesce(bp);
}

/*
* mm_realloc - Implemented simply in terms of mm_malloc and mm_free
*/
void *mm_realloc(void *bp, size_t size) {
	if ((int)size < 0)
		return NULL;
	else if ((int)size == 0) {
		mm_free(bp);
		return NULL;
	}
	else if (size > 0) {
		size_t original_size = GET_SIZE(HDRP(bp));
		size_t new_size = size + 2 * WSIZE; // ����� Ǫ�ͻ�����
		//realloc�� ���� ������� �� ���� ����� ó��
		if (new_size <= original_size) {
			return bp;
		}
		//realloc�� ����������� �� ū ����� ó��
		else {
			size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLK(bp)));
			size_t csize;
			//���࿡ ����� ������� ��쿡�� �׳� �����ְ� �ȵǸ��� place�� �̿��� ó���� �Ѵ�.
			if (!next_alloc && ((csize = original_size + GET_SIZE(HDRP(NEXT_BLK(bp))))) >= new_size) {
				node_remove(NEXT_BLK(bp));
				PUT(HDRP(bp), PACK(csize, 1));
				PUT(FTRP(bp), PACK(csize, 1));
				return bp;
			}
			else {
				void *new_ptr = mm_malloc(new_size);
				place(new_ptr, new_size);
				memcpy(new_ptr, bp, new_size);
				mm_free(bp);
				return new_ptr;
			}
		}
	}
	else
		return NULL;
}

static void *coalesce(void *bp) {

	//������ϰ� ���ĺ���� ���¿� ���� coalesce�ϵ��� ����
	size_t NEXT_ALLOC = GET_ALLOC(HDRP(NEXT_BLK(bp)));
	size_t PREV_ALLOC = GET_ALLOC(FTRP(PREV_BLK(bp))) || PREV_BLK(bp) == bp;
	size_t size = GET_SIZE(HDRP(bp));

	//������ϸ� free�ΰ��
	if (PREV_ALLOC && !NEXT_ALLOC) {
		size += GET_SIZE(HDRP(NEXT_BLK(bp)));
		node_remove(NEXT_BLK(bp));
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
	}
	//������ϸ� free�� ���
	else if (!PREV_ALLOC && NEXT_ALLOC) {
		size += GET_SIZE(HDRP(PREV_BLK(bp)));
		bp = PREV_BLK(bp);
		node_remove(bp);
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
	}
	//���ʴ� free�� ���
	else if (!PREV_ALLOC && !NEXT_ALLOC) {
		size += GET_SIZE(HDRP(PREV_BLK(bp))) + GET_SIZE(HDRP(NEXT_BLK(bp)));
		node_remove(PREV_BLK(bp));
		node_remove(NEXT_BLK(bp));
		bp = PREV_BLK(bp);
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
	}//�������� ���� bp�� return
	node_insert(bp);
	return bp;
}

static void *extend_heap(size_t words) {
	char *bp;
	size_t size;

	//¦����ȣ�� �Ҵ��Ͽ� word����������� �Ҵ�
	size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
	//�̴ϸ� ��ϻ����ŭ�� �Ǿ��ϴ� 16���� ���� �Ҵ��� 16����
	if (size < 16) {
		size = 16;
	}
	//����ó��
	if ((int)(bp = mem_sbrk(size)) == -1) {
		return NULL;
	}
	//�ʱ�ȭ�� ��Ų��.
	PUT(HDRP(bp), PACK(size, 0));        
	PUT(FTRP(bp), PACK(size, 0));         
	PUT(HDRP(NEXT_BLK(bp)), PACK(0, 1)); 
	//�ʱ�ȭ�� ��ħ
	return coalesce(bp);
}

static void *find_fit(size_t asize) {
	//�� �Լ������� fit�Ǵ� �����ġ�� ã���ش�.	
	void *bp;
	static int last_malloced_size = 0;
	static int repeat_counter = 0;
	if (last_malloced_size == (int)asize) {
		if (repeat_counter>30) {
			int extendsize = MAX(asize, 4 * WSIZE);
			bp = extend_heap(extendsize / 4);
			return bp;
		}
		else
			repeat_counter++;
	}
	else
		repeat_counter = 0;
	for (bp = free_list_start; GET_ALLOC(HDRP(bp)) == 0; bp = GET_NEXT_PTR(bp)) {
		if (asize <= (size_t)GET_SIZE(HDRP(bp))) {
			last_malloced_size = asize;
			return bp;
		}
	}
	return NULL;
}

static void place(void *bp, size_t asize) {
	size_t csize = GET_SIZE(HDRP(bp));
	//�� ��Ͽ����� asize ����� bp�� ��ġ�����ֵ��� ��
	if ((csize - asize) >= 4 * WSIZE) {
		PUT(HDRP(bp), PACK(asize, 1));
		PUT(FTRP(bp), PACK(asize, 1));
		node_remove(bp);
		bp = NEXT_BLK(bp);
		PUT(HDRP(bp), PACK(csize - asize, 0));
		PUT(FTRP(bp), PACK(csize - asize, 0));
		coalesce(bp);
	}
	else {
		PUT(HDRP(bp), PACK(csize, 1));
		PUT(FTRP(bp), PACK(csize, 1));
		node_remove(bp);
	}
}

static void node_insert(void *bp) {
	SET_NEXT_PTR(bp, free_list_start);
	SET_PREV_PTR(free_list_start, bp);
	SET_PREV_PTR(bp, NULL);
	free_list_start = bp;
	//global �������� free_list_start�� ��带 �־��ش�.
}

static void node_remove(void *bp) {
	if (GET_PREV_PTR(bp))
		SET_NEXT_PTR(GET_PREV_PTR(bp), GET_NEXT_PTR(bp));
	else
		free_list_start = GET_NEXT_PTR(bp);
	SET_PREV_PTR(GET_NEXT_PTR(bp), GET_PREV_PTR(bp));
	//global �������� free_list_start�� ��带 ���ش�.
}

