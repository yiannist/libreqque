#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "reqque.h"

struct req {
    void *handler_arg;
    int handler_idx;
    callback_t cb;
};

static GAsyncQueue* req_queue;
static handler_t *req_handlers;
static GThread *consumer_thread;

void do_handle_req(struct req *r) {
    void *res;

    handler_t handler = req_handlers[r->handler_idx];
    res = handler(r->handler_arg);
    r->cb(res);
}

void loop() {
    while (1) {
        struct req *r;
        
        r = g_async_queue_pop(req_queue);
        g_thread_new("worker", (GThreadFunc) do_handle_req, r);
    }
}

int reqque_init(handler_t *handlers) {
    req_handlers = handlers;
    req_queue = g_async_queue_new();
    consumer_thread = g_thread_new("handler", (GThreadFunc) loop, NULL);

    return 0;
}

int handle_req(void *arg, int idx, callback_t cb) {
    struct req *r = malloc(sizeof(struct req));

    r->handler_arg = arg;
    r->handler_idx = idx;
    r->cb = cb;

    g_async_queue_push(req_queue, r);

    return 0;
}

/* Testing functions */
int add(int *args) {
    return (args[0] + args[1]);
}

int sub(int *args) {
    return (args[0] - args[1]);
}

void print(int x) {
    printf("Great! Res: %d\n", x);
}

int main(int argc, char **argv) {
    int args[2] = {10, 5};
    handler_t *handlers = malloc(2 * sizeof(handler_t));
    handlers[0] = (handler_t) &add;
    handlers[1] = (handler_t) &sub;

    reqque_init(handlers);

    handle_req((void *) args, 0, (callback_t) &print);
    handle_req((void *) args, 1, (callback_t) &print);
    g_thread_join(consumer_thread);

    return 0;
}
