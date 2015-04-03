#include <glib.h>
#include "queue.h"

/*
    Queue implementation based on Glib thread pools.
*/
Queue init_queue(executer_t handler) {
    return g_thread_pool_new((GFunc) handler, NULL, MAX_THREADS, TRUE, NULL);
}

void enqueue(Queue queue, void *obj) {
    g_thread_pool_push((GThreadPool *) queue, obj, NULL);
}
