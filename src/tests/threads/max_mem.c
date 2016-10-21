#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "threads/malloc.h"
#include "threads/palloc.h"

void
max_mem (void) 
{
	int i;
	char *mas;
	mas=1;

	for(i=1; mas!=NULL; i++)
	{
		mas=NULL;
		//mas=malloc(256);
		//mas=calloc(128, sizeof(int));
		mas = palloc_get_page (PAL_ZERO);
		msg("times = %d",i);
	}
	msg("End with %d times", i);
}
//368 and 736
//malloc - 5462
//calloc - 2550
//palloc - 366
//PG_SIZE - 2^12=4096