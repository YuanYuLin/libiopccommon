#ifndef IOPCCMD_MNTBASEGET_H
#define IOPCCMD_MNTBASEGET_H

#include "iopcdefine.h"

struct req_mntbaseget_t {
    uint8_t index;
}__PACKED__;

struct res_mntbaseget_t {
    uint8_t status;
    uint8_t index;
    uint8_t enabled;
    uint8_t fixed;
    uint8_t name[MNTBASE_NAME_LEN];
    uint8_t src[STR_LEN];
    uint8_t dst[STR_LEN];
    uint8_t type[MNTBASE_TYPE_LEN];
}__PACKED__;

#endif
