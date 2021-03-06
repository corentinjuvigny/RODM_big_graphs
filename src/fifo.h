#ifndef FIO_FIFO_H
#define FIO_FIFO_H

#include <stdlib.h>
#include <string.h>

typedef struct FIFO
{
	unsigned long *buf;
	unsigned long len;
	unsigned long *r;
	unsigned long *w;
	unsigned long cnt;
} FIFO_t;

extern FIFO_t* FIFO_Create(unsigned long len);
extern void FIFO_Flush(FIFO_t* fifo);
extern unsigned long FIFO_Push(FIFO_t* fifo, unsigned long element);
extern unsigned long FIFO_Pop(FIFO_t* fifo);
extern unsigned long FIFO_Peek(FIFO_t* fifo);
extern unsigned long FIFO_IsFull(FIFO_t* fifo);
extern unsigned long FIFO_IsEmpty(FIFO_t* fifo);
extern unsigned long FIFO_GetUsed(FIFO_t* fifo);
extern unsigned long FIFO_GetFree(FIFO_t* fifo);
extern void FIFO_Destroy(FIFO_t* fifo);

typedef struct
{
    unsigned long size;
    unsigned long* p;
} NodeArray;


NodeArray newArray();
static inline unsigned long getBackNode(NodeArray* array)
{
   return array->p[array->size-1];
}

void addNode(NodeArray* array, unsigned long node);

unsigned long popNode(NodeArray* array);

static inline void deleteNode(NodeArray* array, unsigned long idx)
{
    array->p[idx] = getBackNode(array);
    popNode(array);
}

#endif
