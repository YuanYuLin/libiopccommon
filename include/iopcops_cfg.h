#ifndef IOPCOPS_CFG_H
#define IOPCOPS_CFG_H

struct ops_cfg_t {
    void (*init)(void);
};

DEFINE_GET_INSTANCE(cfg, ifc);
DEFINE_DEL_INSTANCE(cfg, ifc);

#define GET_INSTANCE_CFG_IFC() GET_INSTANCE(cfg, ifc)

#endif
