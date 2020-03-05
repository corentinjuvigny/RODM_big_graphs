#include "fifo.h"

FIFO_t* FIFO_Create(unsigned long len)
{
	FIFO_t* fifo = malloc(sizeof(FIFO_t));
	if (fifo == NULL) return NULL;
	fifo->buf = malloc(len * sizeof(len));
	if (fifo->buf == NULL)
	{
		free(fifo);
		fifo = NULL;
		return NULL;
	}
	fifo->len = len;
	fifo->r = fifo->buf;
	fifo->w = fifo->buf;
	fifo->cnt = 0;
	return fifo;
}

void FIFO_Flush(FIFO_t* fifo)
{
	fifo->r = fifo->buf;
	fifo->w = fifo->buf;
	fifo->cnt = 0;
}

unsigned long FIFO_Push(FIFO_t* fifo, unsigned long element)
{
	if (fifo->cnt == fifo->len) {
		return 0;
	}
	*fifo->w = element;
	fifo->w = (fifo->w == (fifo->buf+fifo->len-1)) ? fifo->buf :  fifo->w + 1;
	fifo->cnt++;
	return 1;
}

unsigned long FIFO_Pop(FIFO_t* fifo)
{
	if (fifo->cnt == 0) {
		return 0;
	} else {
		unsigned long data = *fifo->r;
		fifo->r = (fifo->r == (fifo->buf+fifo->len-1)) ? fifo->buf :  fifo->r + 1;
		fifo->cnt--;
		return data;
	}

}

unsigned long FIFO_Peek(FIFO_t* fifo)
{
	if (fifo->cnt == 0) {
		return 0;
	}
	return *fifo->r;
}

unsigned long FIFO_IsFull(FIFO_t* fifo)
{
	return fifo->cnt == fifo->len;
}

unsigned long FIFO_IsEmpty(FIFO_t* fifo)
{
	return fifo->cnt == 0;
}

unsigned long FIFO_GetUsed(FIFO_t* fifo)
{
	return fifo->cnt;
}

unsigned long FIFO_GetFree(FIFO_t* fifo)
{
	return fifo->len - fifo->cnt;
}

void FIFO_Destroy(FIFO_t* fifo)
{
   free(fifo->buf);
	free(fifo);
	fifo = NULL;
}
