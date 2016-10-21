#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

static thread_func do_func;

void 
threads_audit(void)
{
	int count_of_threads=10, i;
    struct DataElement *elem, *DataStart=NULL;
    char *name;

    struct semaphore wait_sema;
    thread_set_priority (PRI_MAX);
	sema_init (&wait_sema, 0);

	for (i = 0; i < count_of_threads; i++)
    {
    	name=malloc(sizeof(char)*16);
    	elem=calloc(1,sizeof(struct DataElement));
    	if(DataStart!=NULL)	elem->next=DataStart;

    	snprintf (name, sizeof(char)*16, "Thread %d", i);
      	elem->name=name;
      	elem->sema=&wait_sema;
      	elem->need_to_work=50*(i % 5);
        elem->start_time=timer_ticks();

    	thread_create (name, PRI_DEFAULT+10-i, do_func, elem);
    	DataStart=elem;
    }

    thread_set_priority (PRI_MIN);
    msg("Lets start show");

    for (i = 0; i < 10; i++)
	    sema_down (&wait_sema);


    for(; elem!=NULL; elem=elem->next)
    {
    	msg("---%s statistics---", elem->name);
    	msg("Start in %d",elem->start_time);
    	msg("Time of work %d",elem->work_time);
    	msg("End in %d",elem->end_time);
    	msg("---end statistics---");
    }
}

static void
do_func (void *aux) 
{
	struct thread *cur=thread_current();
//    struct DataElement *data=aux;
    cur->data_list=aux;


	cur->work_time=timer_ticks();
//	msg("%s is start work",cur->name);
	timer_sleep(cur->data_list->need_to_work);
//	msg("%s is ended work",cur->name);

	cur->data_list->work_time=timer_ticks()-cur->work_time;
	cur->data_list->end_time=timer_ticks();
	sema_up (cur->data_list->sema);
}