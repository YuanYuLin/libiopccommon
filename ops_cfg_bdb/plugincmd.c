#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>

#include "iopcdefine.h"
#include "iopcops_cfg.h"
#include "iopcops_cfg_plugincmd.h"
#include "iopcops_cfg_bdb.h"
#include "iopcops_cfg_bdb_plugincmd.h"

#define PLUGINCMD_SIZE			"plugincmd.cfg.size"
#define PLUGINCMD_ENABLED		"plugincmd.cfg[%d].enabled"
#define PLUGINCMD_FIXED			"plugincmd.cfg[%d].fixed"
#define PLUGINCMD_NAME			"plugincmd.cfg[%d].name"

static void loadall()
{
    GET_INSTANCE(cfg_bdb, ifc)->init();
}

static uint32_t get_size(void)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint32_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PLUGINCMD_SIZE);

    result = GET_UINT32(cfg_str);

    return result;
}

static uint8_t get_enabled(uint8_t idx_cfg)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PLUGINCMD_ENABLED, idx_cfg);

    result = GET_BOOLEAN(cfg_str);

    return result;
}

static void set_enabled(uint8_t idx_cfg, uint8_t cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PLUGINCMD_ENABLED, idx_cfg);

    SET_BOOLEAN(cfg_str, cfg_val);
}

static uint8_t get_fixed(uint8_t idx_cfg)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PLUGINCMD_FIXED, idx_cfg);

    result = GET_BOOLEAN(cfg_str);

    return result;
}

static void set_name(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PLUGINCMD_NAME, idx_cfg);

    SET_STRING(cfg_str, cfg_val);
}

static uint16_t get_name(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PLUGINCMD_NAME, idx_cfg);
    result = GET_STRING(cfg_str, cfg_val);

    return result;
}

DEFINE_INSTANCE(cfg_plugincmd, bdb);
DEFINE_GET_INSTANCE(cfg_plugincmd, bdb)
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

DEFINE_DEL_INSTANCE(cfg_plugincmd, bdb)
{
    if(obj)
        free(obj);
}

