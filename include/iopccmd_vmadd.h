#ifndef IOPCCMD_VMADD_H
#define IOPCCMD_VMADD_H

#include "iopcdefine.h"

struct req_vmadd_t {
    uint8_t auto_start;
    uint8_t name[VM_NAME_LEN];
    uint8_t nettype[VM_NETTYPE_LEN];
    uint8_t nethwlink[VM_NETHWLINK_LEN];
    uint8_t nethwaddr[VM_NETHWADDR_LEN];
    uint8_t base_path[STR_LEN];
}__PACKED__;

struct res_vmadd_t {
    uint8_t status;
    uint8_t index;
}__PACKED__;

#endif
