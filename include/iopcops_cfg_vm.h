#ifndef IOPCOPS_CFG_VM_H
#define IOPCOPS_CFG_VM_H

#include "iopcdefine.h"

struct ops_cfg_vm_t {
    void        (*loadall)(void);
    uint32_t	(*get_cfg_size)(void);
    void	(*set_cfg_size)(uint32_t);
    uint8_t	(*get_autostart)(uint8_t idx_cfg);
    void	(*set_autostart)(uint8_t idx_cfg, uint8_t cfg_val);
    uint16_t	(*get_name)(uint8_t idx_cfg, uint8_t*);
    void	(*set_name)(uint8_t idx_cfg, uint8_t*);
    uint16_t	(*get_base_path)(uint8_t idx_cfg, uint8_t*);
    void	(*set_base_path)(uint8_t idx_cfg, uint8_t*);
    uint16_t	(*get_nettype)(uint8_t idx_cfg, uint8_t*);
    void	(*set_nettype)(uint8_t idx_cfg, uint8_t*);
    uint16_t	(*get_nethwlink)(uint8_t idx_cfg, uint8_t*);
    void	(*set_nethwlink)(uint8_t idx_cfg, uint8_t*);
    uint16_t	(*get_nethwaddr)(uint8_t idx_cfg, uint8_t*);
    void	(*set_nethwaddr)(uint8_t idx_cfg, uint8_t*);
    uint32_t	(*add_vm)(uint8_t, uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
};

DEFINE_GET_INSTANCE(cfg_vm, ifc);
DEFINE_DEL_INSTANCE(cfg_vm, ifc);

#endif
