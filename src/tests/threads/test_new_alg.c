#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/synch.h"
#include "threads/thread.h"

struct AllNeed
{
	int cpu_birst;
	struct semaphore *sema;
};

static thread_func cpu_func;

void
test_new_alg (void) 
{
	int i;
	struct AllNeed data;

  struct semaphore wait_sema;
	sema_init (&wait_sema, 0);

	data.sema=&wait_sema;

	thread_set_priority (PRI_MIN);

  data.cpu_birst=4;
	thread_create ("Proc0", 5,  cpu_func, &data);

	data.cpu_birst=3;
	thread_create ("Proc1", 6,  cpu_func, &data);

	data.cpu_birst=6;
	thread_create ("Proc2", 7,  cpu_func, &data);

	data.cpu_birst=10;
	thread_create ("Proc3", 25, cpu_func, &data);

	data.cpu_birst=2;
	thread_create ("Proc4", 26, cpu_func, &data);

  for (i = 0; i < 5; i++)
    sema_up (data.sema);

  msg("All Done");
}

static void
cpu_func (void *time_sema) 
{
	struct AllNeed *data=time_sema;

	thread_current()->CPU_birst=data->cpu_birst;

	sema_down (data->sema);
	msg ("Thread %s with CPU birst %d.", thread_name (), thread_current()->CPU_birst);

  timer_sleep (thread_current()->CPU_birst);

	  /* Print a message on wake-up. */
 	msg ("Thread %s woke up.", thread_name ());
}
