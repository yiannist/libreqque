#ifndef REQQUE_H
#define REQQUE_H

typedef void  (*callback_t)(void *arg);
typedef void *(*handler_t)(void *arg);

struct reqque_ctx_t {
    handler_t *handlers;
    void *queue;
};

struct req {
    struct reqque_ctx_t *reqque_ctx;
    void *handler_arg;
    int handler_idx;
    callback_t cb;
};

struct reqque_ctx_t *reqque_init(handler_t *handlers);
int submit_req(struct reqque_ctx_t *ctx, void *handler_arg, int handler_idx,
               callback_t cb);

#endif /* REQQUE_H */
