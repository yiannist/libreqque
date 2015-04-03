#include <stdio.h>
#include <stdlib.h>
#include "reqque.h"
#include "queue.h"

void do_handle_req(void *arg, void *data) {
    struct req *r = (struct req *) arg;
    struct reqque_ctx_t *ctx = r->reqque_ctx;
    handler_t handler = ctx->handlers[r->handler_idx];

    handler(r);
}

struct reqque_ctx_t *reqque_init(handler_t *handlers) {
    struct reqque_ctx_t *reqque_ctx = malloc(sizeof(struct reqque_ctx_t));

    reqque_ctx->handlers = handlers;
    reqque_ctx->queue = init_queue(&do_handle_req);

    return reqque_ctx;
}

int submit_req(struct reqque_ctx_t *ctx, void *arg, int idx, callback_t cb) {
    struct req *r = malloc(sizeof(struct req));

    r->reqque_ctx = ctx;
    r->handler_arg = arg;
    r->handler_idx = idx;
    r->cb = cb;

    enqueue(ctx->queue, r);

    return 0;
}

/* Testing functions */
void add(void *arg) {
    struct req *r = (struct req *) arg;
    int *args = (int *) r->handler_arg;
    int a = args[0];
    int b = args[1];
    int res = a + b;

    r->cb((void *) &res);
}

void sub(void *arg) {
    struct req *r = (struct req*) arg;
    int *args = (int *) r->handler_arg;
    int a = args[0];
    int b = args[1];
    int res = a - b;

    r->cb((void *) &res);
}

void print(void *arg) {
    int *x = (int *) arg;
    printf("Great! Res: %d.\n", *x);
}

#define ADD 0
#define SUB 1

int main(int argc, char **argv) {
    int args[2] = {10, 5};
    handler_t handlers[2] = {(handler_t) &add, (handler_t) &sub};
    struct reqque_ctx_t *reqque_ctx;

    reqque_ctx = reqque_init(handlers);

    submit_req(reqque_ctx, (void *) args, ADD, (callback_t) &print);
    submit_req(reqque_ctx, (void *) args, SUB, (callback_t) &print);
    submit_req(reqque_ctx, (void *) args, ADD, (callback_t) &print);

    sleep(1);

    return 0;
}
