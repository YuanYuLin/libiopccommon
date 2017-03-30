#ifndef IOPCOPS_CFG_STATUS_H
#define IOPCOPS_CFG_STATUS_H

#include "iopcdefine.h"

struct ops_cfg_status_t {
    void (*set_service_starting)(uint8_t* name);
    void (*set_service_started)(uint8_t* name);
    void (*set_service_stoping)(uint8_t* name);
    void (*set_service_stoped)(uint8_t* name);
    uint8_t (*is_service_started)(uint8_t* name);
    uint8_t (*is_service_stoped)(uint8_t* name);
    void (*wait_service_started)(uint8_t* name);
    void (*wait_service_stoped)(uint8_t* name);
    uint32_t (*get_service_status)(uint8_t* name);
    uint32_t (*get_progress_status)(uint8_t* name);
    void (*set_progress_status)(uint8_t* name, uint32_t status);
};

DEFINE_GET_INSTANCE(cfg_status, ifc);
DEFINE_DEL_INSTANCE(cfg_status, ifc);

#endif
