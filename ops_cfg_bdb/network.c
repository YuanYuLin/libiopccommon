#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "iopcdefine.h"
#include "iopcops_cfg.h"
#include "iopcops_cfg_network.h"
#include "iopcops_cfg_bdb.h"
#include "iopcops_cfg_bdb_network.h"
#include "iopcops_misc.h"

#define NETDEV_SIZE		"network.cfg.size"
#define NETDEV_TYPE		"network.cfg[%d].type"
#define IFC_NAME		"network.cfg[%d].interface_name"
#define IS_UP			"network.cfg[%d].is_up"
#define IS_DHCP			"network.cfg[%d].is_dhcp"
#define IS_SETUP_IPADDRESS	"network.cfg[%d].is_setup_ipaddress"
#define IS_SETUP_HWADDRESS	"network.cfg[%d].is_setup_hwaddress"
#define NETDEV_HWADDRESS	"network.cfg[%d].hwaddress"
#define IFC_SIZE		"network.cfg[%d].interfaces.size"
#define CONSIST_IFCS		"network.cfg[%d].interfaces[%d].name"
#define IFC_IPADDRESS		"network.cfg[%d].interface_address"
#define IFC_IPNETMASK		"network.cfg[%d].interface_netmask"

#define NETWORK_READY		network.ready

static void loadall()
{
    GET_INSTANCE(cfg_bdb, ifc)->init();
}

static uint32_t get_no_of_networks()
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, NETDEV_SIZE);
    return GET_UINT32(cfg_str);
}

static uint8_t get_network_type(uint8_t ifc_idx)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t cfg_val[STR_LEN] = {0};
    uint8_t* ptr = &cfg_val[0];
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    memset(cfg_val, 0, STR_LEN);
    sprintf(cfg_str, NETDEV_TYPE, ifc_idx);
    result = GET_STRING(cfg_str, ptr);

    if(result != strlen(cfg_val))
        printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    if(strcmp("generic", cfg_val) == 0) {
        return NETWORK_GENERIC;
    }

    if(strcmp("bridge", cfg_val) == 0) {
        return NETWORK_BRIDGE;
    }

    if(strcmp("vlan", cfg_val) == 0) {
        return NETWORK_VLAN;
    }

    return NETWORK_UNKNOW;
}

static uint16_t get_interface_name(uint8_t ifc_idx, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, IFC_NAME, ifc_idx);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
        printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static uint8_t is_up(uint8_t ifc_idx)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, IS_UP, ifc_idx);
    return GET_BOOLEAN(cfg_str);
}

static uint8_t is_dhcp(uint8_t ifc_idx)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, IS_DHCP, ifc_idx);
    return GET_BOOLEAN(cfg_str);
}

static uint8_t is_setup_ipaddress(uint8_t ifc_idx)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, IS_SETUP_IPADDRESS, ifc_idx);
    return GET_BOOLEAN(cfg_str);
}

static uint8_t is_setup_hwaddress(uint8_t ifc_idx)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, IS_SETUP_HWADDRESS, ifc_idx);
    return GET_BOOLEAN(cfg_str);
}

static uint16_t get_hwaddress(uint8_t ifc_idx, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, NETDEV_HWADDRESS, ifc_idx);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
        printf("[%s]index %d: error len(%d,%d)\n", __func__, ifc_idx, result, strlen(cfg_val));

    return result;
}

static uint16_t get_ipaddress(uint8_t ifc_idx, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, IFC_IPADDRESS, ifc_idx);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
        printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static uint16_t get_ipnetmask(uint8_t ifc_idx, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, IFC_IPNETMASK, ifc_idx);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
        printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static uint32_t get_no_of_consist_interfaces(uint8_t ifc_idx)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, IFC_SIZE, ifc_idx);
    return GET_UINT32(cfg_str);
}

static uint16_t get_consist_interfaces(uint8_t ifc_idx, uint8_t consist_ifc_idx, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    memset(cfg_val, 0, MAX_STR_VAL);
    sprintf(cfg_str, CONSIST_IFCS, ifc_idx, consist_ifc_idx);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
        printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

//static struct ops_cfg_bdb_network_t* obj = NULL;

DEFINE_INSTANCE(cfg_network, bdb);
DEFINE_GET_INSTANCE(cfg_network, bdb)
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

DEFINE_DEL_INSTANCE(cfg_network, bdb)
{
    if(obj)
        free(obj);
}
