#ifndef IOPC_MNTBASEINFO_H
#define IOPC_MNTBASEINFO_H

#include "iopcdefine.h"

struct mntbase_info_t {
    uint8_t enabled;
    uint8_t fixed;
    uint8_t name[MNTBASE_NAME_LEN];
    uint8_t src[STR_LEN];
    uint8_t dst[STR_LEN];
    uint8_t type[MNTBASE_TYPE_LEN];
}__PACKED__;

#endif
