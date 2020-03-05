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

FIFO_t* FIFO_Create(unsigned long len);
void FIFO_Flush(FIFO_t* fifo);
unsigned long FIFO_Push(FIFO_t* fifo, unsigned long element);
unsigned long FIFO_Pop(FIFO_t* fifo);
unsigned long FIFO_Peek(FIFO_t* fifo);
unsigned long FIFO_IsFull(FIFO_t* fifo);
unsigned long FIFO_IsEmpty(FIFO_t* fifo);
unsigned long FIFO_GetUsed(FIFO_t* fifo);
unsigned long FIFO_GetFree(FIFO_t* fifo);
void FIFO_Destroy(FIFO_t* fifo);

#endif
