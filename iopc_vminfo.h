#ifndef IOPC_VMINFO_H
#define IOPC_VMINFO_H

#include "iopcdefine.h"

struct vm_info_t {
//    uint8_t index;
    uint8_t auto_start;
    uint8_t name[VM_NAME_LEN];
    uint8_t base_path[STR_LEN];
    uint8_t nettype[VM_NETTYPE_LEN];
    uint8_t nethwlink[VM_NETHWLINK_LEN];
    uint8_t nethwaddr[VM_NETHWADDR_LEN];
};

#endif
