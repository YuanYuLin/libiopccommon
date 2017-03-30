#ifndef IOPCCMD_MNTBASECOUNT_H
#define IOPCCMD_MNTBASECOUNT_H

#include "iopcdefine.h"

struct req_mntbasecount_t {
}__PACKED__;

struct res_mntbasecount_t {
    uint8_t status;
    uint8_t count;
}__PACKED__;

#endif
