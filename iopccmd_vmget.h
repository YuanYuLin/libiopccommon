#ifndef IOPCCMD_VMGET_H
#define IOPCCMD_VMGET_H

#include "iopcdefine.h"

struct req_vmget_t {
    uint8_t index;
}__PACKED__;

struct res_vmget_t {
    uint8_t status;
    uint8_t index;
    uint8_t auto_start;
    uint8_t name[VM_NAME_LEN];
    uint8_t nettype[VM_NETTYPE_LEN];
    uint8_t nethwlink[VM_NETHWLINK_LEN];
    uint8_t nethwaddr[VM_NETHWADDR_LEN];
    uint8_t base_path[STR_LEN];
}__PACKED__;

#endif
