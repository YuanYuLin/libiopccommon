#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "iopcops_cfg_bdb_network.h"

static void loadall()
{
    GET_INSTANCE(cfg_network, bdb)->loadall();
}

static uint32_t get_no_of_networks()
{
    uint32_t result = 0;

    result = GET_INSTANCE(cfg_network, bdb)->get_no_networks();

    return result;
}

static uint8_t get_network_type(uint8_t ifc_idx)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_network, bdb)->get_type(ifc_idx);

    return result;
}

static uint16_t get_interface_name(uint8_t ifc_idx, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_network, bdb)->get_interface_name(ifc_idx, cfg_val);

    return result;
}

static uint8_t is_up(uint8_t ifc_idx)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_network, bdb)->is_up(ifc_idx);

    return result;
}

static uint8_t is_dhcp(uint8_t ifc_idx)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_network, bdb)->is_dhcp(ifc_idx);

    return result;
}

static uint8_t is_setup_ipaddress(uint8_t ifc_idx)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_network, bdb)->is_setup_ipaddress(ifc_idx);

    return result;
}

static uint8_t is_setup_hwaddress(uint8_t ifc_idx)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_network, bdb)->is_setup_hwaddress(ifc_idx);

    return result;
}

static uint16_t get_hwaddress(uint8_t ifc_idx, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_network, bdb)->get_hwaddress(ifc_idx, cfg_val);

    return result;
}

static uint16_t get_ipaddress(uint8_t ifc_idx, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_network, bdb)->get_ipaddress(ifc_idx, cfg_val);

    return result;
}

static uint16_t get_ipnetmask(uint8_t ifc_idx, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_network, bdb)->get_ipnetmask(ifc_idx, cfg_val);

    return result;
}

static uint32_t get_no_of_consist_interfaces(uint8_t ifc_idx)
{
    uint32_t result = 0;

    result = GET_INSTANCE(cfg_network, bdb)->get_no_consist_interfaces(ifc_idx);

    return result;
}

static uint16_t get_consist_interfaces(uint8_t ifc_idx, uint8_t consist_ifc_idx, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_network, bdb)->get_consist_interfaces(ifc_idx, consist_ifc_idx, cfg_val);

    return result;
}

DEFINE_INSTANCE(cfg_network, ifc);
DEFINE_GET_INSTANCE(cfg_network, ifc)
{
    if(!obj) {
        obj = malloc(sizeof(struct ops_cfg_network_t));
	obj->loadall = loadall;
	obj->get_no_networks = get_no_of_networks;
	obj->get_type = get_network_type;
	obj->get_interface_name = get_interface_name;
	obj->get_ipaddress = get_ipaddress;
	obj->get_ipnetmask = get_ipnetmask;
	obj->is_up = is_up;
	obj->is_dhcp = is_dhcp;
	obj->is_setup_ipaddress = is_setup_ipaddress;
	obj->is_setup_hwaddress = is_setup_hwaddress;
	obj->get_hwaddress = get_hwaddress;
	obj->get_no_consist_interfaces = get_no_of_consist_interfaces;
	obj->get_consist_interfaces = get_consist_interfaces;
    }

    return obj;
}

DEFINE_DEL_INSTANCE(cfg_network, ifc)
{
    if(obj)
        free(obj);
}
