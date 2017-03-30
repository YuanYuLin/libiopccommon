#ifndef IOPC_RAIDDEVINFO_H
#define IOPC_RAIDDEVINFO_H

#include "iopcdefine.h"

struct raiddev_t {
    uint8_t enabled;
    uint8_t path[RAIDDEV_PATH_LEN];
}__PACKED__;

struct raiddev_info_t {
    uint8_t enabled;
    uint8_t name[RAIDDEV_NAME_LEN];
    uint8_t type[RAIDDEV_TYPE_LEN];
    uint8_t dev_size;
    struct raiddev_t dev[MAX_RAID_COUNT];
}__PACKED__;

#endif
