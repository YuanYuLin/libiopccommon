#ifndef CLIENT_MNTBASE_H
#define CLIENT_MNTBASE_H

#include "iopc_mntbaseinfo.h"

struct ops_client_mntbase_t {
    uint32_t (*count)();
    int (*set)(uint8_t index, struct mntbase_info_t* info);
    int (*get)(uint8_t index, struct mntbase_info_t* info);
};

DEFINE_GET_INSTANCE(client_mntbase, obj);
DEFINE_DEL_INSTANCE(client_mntbase, obj);

#define GET_INSTANCE_CLIENT_MNTBASE() GET_INSTANCE(client_mntbase, obj)

#endif
