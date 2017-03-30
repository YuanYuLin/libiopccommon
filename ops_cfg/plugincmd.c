#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>

#include "iopcops_cfg_bdb_plugincmd.h"

static void loadall()
{
    GET_INSTANCE(cfg_plugincmd, bdb)->loadall();
}

static uint32_t get_size(void)
{
    uint32_t result = 0;

    result = GET_INSTANCE(cfg_plugincmd, bdb)->get_size();

    return result;
}

static uint8_t get_enabled(uint8_t idx_cfg)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_plugincmd, bdb)->get_enabled(idx_cfg);

    return result;
}

static void set_enabled(uint8_t idx_cfg, uint8_t cfg_val)
{
    GET_INSTANCE(cfg_plugincmd, bdb)->set_enabled(idx_cfg, cfg_val);
}

static uint8_t get_fixed(uint8_t idx_cfg)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_plugincmd, bdb)->get_fixed(idx_cfg);

    return result;
}

static void set_name(uint8_t idx_cfg, uint8_t* cfg_val)
{
    GET_INSTANCE(cfg_plugincmd, bdb)->set_name(idx_cfg, cfg_val);
}

static uint16_t get_name(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_plugincmd, bdb)->get_name(idx_cfg, cfg_val);

    return result;
}

DEFINE_INSTANCE(cfg_plugincmd, ifc);
DEFINE_GET_INSTANCE(cfg_plugincmd, ifc)
{
    if(!obj) {
        obj = malloc(sizeof(struct ops_cfg_plugincmd_t));
	obj->loadall = loadall;
	obj->get_size = get_size;
	obj->get_enabled = get_enabled;
	obj->set_enabled = set_enabled;
	obj->get_fixed = get_fixed;
	obj->get_name = get_name;
	obj->set_name = set_name;
    }

    return obj;
}

DEFINE_DEL_INSTANCE(cfg_plugincmd, ifc)
{
    if(obj)
        free(obj);
}

