#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>

#include "iopcdefine.h"
#include "iopcops_cfg.h"
#include "iopcops_cfg_vm.h"
#include "iopcops_cfg_bdb.h"
#include "iopcops_cfg_bdb_vm.h"

#define VM_SIZE			"vm.cfg.size"
#define VM_AUTOSTART		"vm.cfg[%d].autostart"
#define VM_NAME			"vm.cfg[%d].name"
#define VM_BASE_PATH		"vm.cfg[%d].base_path"
#define VM_NETTYPE		"vm.cfg[%d].nettype"
#define VM_NETHWLINK		"vm.cfg[%d].nethwlink"
#define VM_NETHWADDR		"vm.cfg[%d].nethwaddr"

static void loadall()
{
    GET_INSTANCE(cfg_bdb, ifc)->init();
}

static uint32_t get_cfg_size(void)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint32_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_SIZE);

    result = GET_UINT32(cfg_str);

    return result;
}

static void set_cfg_size(uint32_t cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_SIZE);
    SET_UINT32(cfg_str, cfg_val);
}

static uint8_t get_autostart(uint8_t idx_cfg)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_AUTOSTART, idx_cfg);

    result = GET_BOOLEAN(cfg_str);

    return result;
}

static void set_autostart(uint8_t idx_cfg, uint8_t cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_AUTOSTART, idx_cfg);

    SET_BOOLEAN(cfg_str, cfg_val);
}

static uint16_t get_name(uint8_t idx_cfg, uint8_t* cfg_val) 
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_NAME, idx_cfg);

    result = GET_STRING(cfg_str, cfg_val);

    return result;
}

static void set_name(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_NAME, idx_cfg);

    SET_STRING(cfg_str, cfg_val);
}

static uint16_t get_base_path(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_BASE_PATH, idx_cfg);
    result = GET_STRING(cfg_str, cfg_val);

    return result;
}

static void set_base_path(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_BASE_PATH, idx_cfg);

    SET_STRING(cfg_str, cfg_val);
}

static uint16_t get_nettype(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_NETTYPE, idx_cfg);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
	    printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static void set_nettype(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_NETTYPE, idx_cfg);
    
    SET_STRING(cfg_str, cfg_val);
}

static uint16_t get_nethwlink(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_NETHWLINK, idx_cfg);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
	    printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static void set_nethwlink(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_NETHWLINK, idx_cfg);

    SET_STRING(cfg_str, cfg_val);
}

static uint16_t get_nethwaddr(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_NETHWADDR, idx_cfg);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
	    printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static void set_nethwaddr(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, VM_NETHWADDR, idx_cfg);

    SET_STRING(cfg_str, cfg_val);
}

static void set_vm(uint8_t idx_cfg, uint8_t autostart, uint8_t* name, uint8_t* base_path, uint8_t* nettype, uint8_t* nethwlink, uint8_t* nethwaddr)
{
    set_name(idx_cfg, name);
    set_autostart(idx_cfg, autostart);
    set_base_path(idx_cfg, base_path);
    set_nettype(idx_cfg, nettype);
    set_nethwlink(idx_cfg, nethwlink);
    set_nethwaddr(idx_cfg, nethwaddr);
}

static uint32_t add_vm(uint8_t autostart, uint8_t* name, uint8_t* base_path, uint8_t* nettype, uint8_t* nethwlink, uint8_t* nethwaddr)
{
    uint32_t cfg_size = get_cfg_size();
    set_cfg_size(cfg_size + 1);
    set_vm(autostart, cfg_size, name, base_path, nettype, nethwlink, nethwaddr);
    return cfg_size;
}

//static struct ops_cfg_bdb_vm_t* obj = NULL;

DEFINE_INSTANCE(cfg_vm, bdb);
DEFINE_GET_INSTANCE(cfg_vm, bdb)
{
    if(!obj) {
        obj = malloc(sizeof(struct ops_cfg_vm_t));
	obj->loadall = loadall;
	obj->get_cfg_size = get_cfg_size;
	obj->set_cfg_size = set_cfg_size;
	obj->get_name = get_name;
	obj->set_name = set_name;
	obj->get_base_path = get_base_path;
	obj->set_base_path = set_base_path;
	obj->get_nettype = get_nettype;
	obj->set_nettype = set_nettype;
	obj->get_nethwlink = get_nethwlink;
	obj->set_nethwlink = set_nethwlink;
	obj->get_nethwaddr = get_nethwaddr;
	obj->set_nethwaddr = set_nethwaddr;
	obj->get_autostart = get_autostart;
	obj->set_autostart = set_autostart;
//	obj->set_vm = set_vm;
	obj->add_vm = add_vm;
    }

    return obj;
}

DEFINE_DEL_INSTANCE(cfg_vm, bdb)
{
    if(obj)
        free(obj);
}

