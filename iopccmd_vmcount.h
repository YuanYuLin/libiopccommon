#ifndef IOPCCMD_VMCOUNT_H
#define IOPCCMD_VMCOUNT_H

#include "iopcdefine.h"

struct req_vmcount_t {
}__PACKED__;

struct res_vmcount_t {
    uint8_t status;
    uint8_t count;
}__PACKED__;

#endif
