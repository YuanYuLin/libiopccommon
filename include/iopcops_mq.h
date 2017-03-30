#ifndef IOPCMQ_H
#define IOPCMQ_H

#include <mqueue.h>

struct ops_mq_t {
    mqd_t (*create)(uint8_t*);
    int (*get)(mqd_t, struct msg_t*);
    int (*set)(mqd_t, struct msg_t*);
    void (*destroy)(uint8_t*);
    int (*get_from)(uint8_t*, struct msg_t*);
    int (*set_to)(uint8_t*, struct msg_t*);
};

//extern struct ops_mq_t ops_mq;
DEFINE_GET_INSTANCE(mq, obj);
DEFINE_DEL_INSTANCE(mq, obj);
#endif
