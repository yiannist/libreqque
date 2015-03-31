#ifndef QUEUE_H
#define QUEUE_H

/* enum req_state { */
/*     SUBMITTED, */
/*     PROCESSING, */
/*     COMPLETED */
/* }; */

typedef void  (*callback_t)(void *arg);
typedef void *(*handler_t)(void *arg);

int reqque_init(handler_t *handlers);
int handle_req(void *arg, int handler_idx, callback_t cb);

#endif /* QUEUE_H */
