#ifndef QUEUE_H
#define QUEUE_H

#define MAX_THREADS 50

typedef void* Queue;
typedef void (*executer_t)(void *arg, void *data);

Queue init_queue(executer_t handler);
void enqueue(Queue queue, void *obj);

#endif /* QUEUE_H */
