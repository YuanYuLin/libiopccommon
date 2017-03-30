#ifndef IOPCCMD_RAIDDEVCOUNT_H
#define IOPCCMD_RAIDDEVCOUNT_H

#include "iopcdefine.h"

struct req_raiddevcount_t {
}__PACKED__;

struct res_raiddevcount_t {
    uint8_t status;
    uint8_t count;
}__PACKED__;

#endif
