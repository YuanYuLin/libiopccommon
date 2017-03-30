#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>

#include "iopcops_cfg_bdb_mountfs.h"

static void loadall()
{
    GET_INSTANCE(cfg_mountfs, bdb)->loadall();
}

static uint32_t get_no_of_size()
{
    uint32_t result = 0;

    result = GET_INSTANCE(cfg_mountfs, bdb)->get_no_of_size();

    return result;
}

static uint8_t is_fixed(uint8_t idx_cfg)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_mountfs, bdb)->is_fixed(idx_cfg);

    return result;
}

static uint16_t get_name(uint8_t idx_cfg, uint8_t* cfg_val) 
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_mountfs, bdb)->get_name(idx_cfg, cfg_val);

    return result;
}

static uint16_t get_dst(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_mountfs, bdb)->get_dst(idx_cfg, cfg_val);

    return result;
}

static uint16_t get_src(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_mountfs, bdb)->get_src(idx_cfg, cfg_val);

    return result;
}

DEFINE_INSTANCE(cfg_mountfs, ifc);
DEFINE_GET_INSTANCE(cfg_mountfs, ifc)
{
    if(!obj) {
        obj = malloc(sizeof(struct ops_cfg_mountfs_t));
	obj->loadall = loadall;
	obj->get_no_of_size = get_no_of_size;
	obj->get_name = get_name;
	obj->is_fixed = is_fixed;
	obj->get_dst = get_dst;
	obj->get_src = get_src;
    }

    return obj;
}

DEFINE_DEL_INSTANCE(cfg_mountfs, ifc)
{
    if(obj)
        free(obj);
}

