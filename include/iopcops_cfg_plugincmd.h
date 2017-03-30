#ifndef IOPCOPS_CFG_PLUGINCMD_H
#define IOPCOPS_CFG_PLUGINCMD_H

#include "iopcdefine.h"

struct ops_cfg_plugincmd_t {
    void        (*loadall)(void);
    uint32_t	(*get_size)(void);
    uint8_t	(*get_enabled)(uint8_t idx_cfg);
    void	(*set_enabled)(uint8_t idx_cfg, uint8_t cfg_val);
    uint8_t	(*get_fixed)(uint8_t idx_cfg);
    uint16_t	(*get_name)(uint8_t idx_cfg, uint8_t*);
    void	(*set_name)(uint8_t idx_cfg, uint8_t*);
};

DEFINE_GET_INSTANCE(cfg_plugincmd, ifc);
DEFINE_DEL_INSTANCE(cfg_plugincmd, ifc);

#endif
