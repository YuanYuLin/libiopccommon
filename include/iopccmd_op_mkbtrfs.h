#ifndef IOPCCMD_OP_MKBTRFS_H
#define IOPCCMD_OP_MKBTRFS_H

#include "iopc_raiddevinfo.h"

struct req_mkbtrfs_t {
    uint8_t type[RAIDDEV_TYPE_LEN];
    uint8_t dev_size;
    struct raiddev_t dev[MAX_RAID_COUNT];
}__PACKED__;

struct res_mkbtrfs_t {
    uint8_t status;
    uint8_t progress_id;
}__PACKED__;

struct req_mkbtrfs_status_t {
    uint8_t progress_id;
}__PACKED__;

struct res_mkbtrfs_status_t {
    uint8_t status;
    uint32_t progress_status;
}__PACKED__;

#endif
