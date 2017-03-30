#ifndef IOPCOPS_CFG_NETWORK_H
#define IOPCOPS_CFG_NETWORK_H

#include "iopcdefine.h"

struct ops_cfg_network_t {
    void	(*loadall)(void);
    uint32_t	(*get_no_networks)(void);
    uint8_t	(*get_type)(uint8_t);
    uint16_t 	(*get_interface_name)(uint8_t, uint8_t*);
    uint16_t	(*get_ipnetmask)(uint8_t, uint8_t*);
    uint16_t	(*get_ipaddress)(uint8_t, uint8_t*);
    uint8_t 	(*is_up)(uint8_t);
    uint8_t	(*is_dhcp)(uint8_t);
    uint8_t	(*is_setup_ipaddress)(uint8_t);
    uint8_t 	(*is_setup_hwaddress)(uint8_t);
    uint16_t 	(*get_hwaddress)(uint8_t, uint8_t*);
    uint32_t 	(*get_no_consist_interfaces)(uint8_t);
    uint16_t 	(*get_consist_interfaces)(uint8_t, uint8_t, uint8_t*);
};

DEFINE_GET_INSTANCE(cfg_network, ifc);
DEFINE_DEL_INSTANCE(cfg_network, ifc);

#endif
