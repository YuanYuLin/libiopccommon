#ifndef CLIENT_VM_H
#define CLIENT_VM_H

#include "iopc_vminfo.h"

struct client_vm_t {
    uint32_t (*count)();
    int (*set)(uint8_t index, struct vm_info_t* info);
    int (*get)(uint8_t index, struct vm_info_t* info);
};

DEFINE_GET_INSTANCE(client_vm);
DEFINE_DEL_INSTANCE(client_vm);

#endif
