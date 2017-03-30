#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>

#include "iopcops_cfg_bdb_vm.h"

static void loadall()
{
    GET_INSTANCE(cfg_vm, bdb)->loadall();
}

static uint32_t get_cfg_size(void)
{
    uint32_t result = 0;

    result = GET_INSTANCE(cfg_vm, bdb)->get_cfg_size();

    return result;
}

static void set_cfg_size(uint32_t cfg_val)
{
    GET_INSTANCE(cfg_vm, bdb)->set_cfg_size(cfg_val);
}

static uint8_t get_autostart(uint8_t idx_cfg)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_vm, bdb)->get_autostart(idx_cfg);

    return result;
}

static void set_autostart(uint8_t idx_cfg, uint8_t cfg_val)
{
    GET_INSTANCE(cfg_vm, bdb)->set_autostart(idx_cfg, cfg_val);
}

static uint16_t get_name(uint8_t idx_cfg, uint8_t* cfg_val) 
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_vm, bdb)->get_name(idx_cfg, cfg_val);

    return result;
}

static void set_name(uint8_t idx_cfg, uint8_t* cfg_val)
{
    GET_INSTANCE(cfg_vm, bdb)->set_name(idx_cfg, cfg_val);
}

static uint16_t get_base_path(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_vm, bdb)->get_base_path(idx_cfg, cfg_val);

    return result;
}

static void set_base_path(uint8_t idx_cfg, uint8_t* cfg_val)
{
    GET_INSTANCE(cfg_vm, bdb)->set_base_path(idx_cfg, cfg_val);
}

static uint16_t get_nettype(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_vm, bdb)->get_nettype(idx_cfg, cfg_val);

    return result;
}

static void set_nettype(uint8_t idx_cfg, uint8_t* cfg_val)
{
    GET_INSTANCE(cfg_vm, bdb)->get_nettype(idx_cfg, cfg_val);
}

static uint16_t get_nethwlink(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_vm, bdb)->get_nethwlink(idx_cfg, cfg_val);

    return result;
}

static void set_nethwlink(uint8_t idx_cfg, uint8_t* cfg_val)
{
    GET_INSTANCE(cfg_vm, bdb)->set_nethwlink(idx_cfg, cfg_val);
}

static uint16_t get_nethwaddr(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_vm, bdb)->get_nethwaddr(idx_cfg, cfg_val);

    return result;
}

static void set_nethwaddr(uint8_t idx_cfg, uint8_t* cfg_val)
{
//    GET_INSTANCE(cfg_vm, bdb)->set_nethwaddr(idx_cfg, cfg_val);
}

/*
static void set_vm(uint8_t idx_cfg, uint8_t autostart, uint8_t* name, uint8_t* base_path, uint8_t* nettype, uint8_t* nethwlink, uint8_t* nethwaddr)
{

    GET_INSTANCE(cfg_vm, bdb)->set_vm(idx_cfg, autostart, name, base_path, nettype, nethwlink, nethwaddr);

}
*/
static uint32_t add_vm(uint8_t autostart, uint8_t* name, uint8_t* base_path, uint8_t* nettype, uint8_t* nethwlink, uint8_t* nethwaddr)
{
    uint32_t result;

    result = GET_INSTANCE(cfg_vm, bdb)->add_vm(autostart, name, base_path, nettype, nethwlink, nethwaddr);

    return result;
}

//static struct ops_cfg_bdb_vm_t* obj = NULL;

DEFINE_INSTANCE(cfg_vm, ifc);
DEFINE_GET_INSTANCE(cfg_vm, ifc)
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

DEFINE_DEL_INSTANCE(cfg_vm, ifc)
{
    if(obj)
        free(obj);
}

