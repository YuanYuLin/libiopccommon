#ifndef CLIENT_RAIDDEV_H
#define CLIENT_RAIDDEV_H

#include "iopc_raiddevinfo.h"

struct ops_client_raiddev_t {
    uint32_t (*count)();
    int (*set)(uint8_t index, struct raiddev_info_t* info);
    int (*get)(uint8_t index, struct raiddev_info_t* info);
};

DEFINE_GET_INSTANCE(client_raiddev);
DEFINE_DEL_INSTANCE(client_raiddev);

#endif
