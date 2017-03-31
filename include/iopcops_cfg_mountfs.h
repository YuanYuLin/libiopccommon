#ifndef IOPCOPS_CFG_MOUNTFS_H
#define IOPCOPS_CFG_MOUNTFS_H

#include "iopcdefine.h"

struct ops_cfg_mountfs_t {
    void (*loadall)(void);
    uint32_t (*get_no_of_size)();
    uint16_t (*get_name)(uint8_t idx_cfg, uint8_t* cfg_val);
    uint8_t (*is_fixed)(uint8_t idx_cfg);
    uint16_t (*get_dst)(uint8_t idx_cfg, uint8_t* cfg_val);
    uint16_t (*get_src)(uint8_t idx_cfg, uint8_t* cfg_val);
};

DEFINE_GET_INSTANCE(cfg_mountfs, ifc);
DEFINE_DEL_INSTANCE(cfg_mountfs, ifc);

#define GET_INSTANCE_CFG_MOUNTFS() GET_INSTANCE(cfg_mountfs, ifc)
#endif
