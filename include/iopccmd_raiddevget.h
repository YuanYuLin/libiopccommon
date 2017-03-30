#ifndef IOPCCMD_RAIDDEVGET_H
#define IOPCCMD_RAIDDEVGET_H

#include "iopc_raiddevinfo.h"

struct req_raiddevget_t {
    uint8_t index;
}__PACKED__;

struct res_raiddevget_t {
    uint8_t status;
    uint8_t index;
    uint8_t enabled;
    uint8_t name[RAIDDEV_NAME_LEN];
    uint8_t type[RAIDDEV_TYPE_LEN];
    uint8_t dev_size;
    struct raiddev_t dev[MAX_RAID_COUNT];
}__PACKED__;

#endif
