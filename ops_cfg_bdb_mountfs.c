#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>

#include "iopcdefine.h"
#include "iopcops_cfg_bdb.h"
#include "iopcops_cfg_bdb_mountfs.h"

#define MOUNTFS_SIZE		"mountfs.cfg.size"
#define MOUNTFS_NAME		"mountfs.cfg[%d].name"
#define IS_FIXED		"mountfs.cfg[%d].fixed"
#define MOUNTFS_DST		"mountfs.cfg[%d].dst"
#define MOUNTFS_SRC		"mountfs.cfg[%d].src"

static void loadall()
{
    GET_INSTANCE(ops_cfg_bdb)->init();
}

static uint32_t get_no_of_size()
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, MOUNTFS_SIZE);

    return GET_UINT32(cfg_str);
}

static uint8_t is_fixed(uint8_t idx_cfg)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, IS_FIXED, idx_cfg);
    result = GET_BOOLEAN(cfg_str);

    if(result)
        return 1;
    return 0;
}

static uint16_t get_name(uint8_t idx_cfg, uint8_t* cfg_val) 
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, MOUNTFS_NAME, idx_cfg);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
        printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static uint16_t get_dst(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, MOUNTFS_DST, idx_cfg);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
        printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static uint16_t get_src(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, MOUNTFS_SRC, idx_cfg);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
        printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

//static struct ops_cfg_bdb_mountfs_t* obj = NULL;

DEFINE_INSTANCE(ops_cfg_bdb_mountfs);
DEFINE_GET_INSTANCE(ops_cfg_bdb_mountfs)
{
    if(!obj) {
        obj = malloc(sizeof(struct ops_cfg_bdb_mountfs_t));
	obj->loadall = loadall;
	obj->get_no_of_size = get_no_of_size;
	obj->get_name = get_name;
	obj->is_fixed = is_fixed;
	obj->get_dst = get_dst;
	obj->get_src = get_src;
    }

    return obj;
}

DEFINE_DEL_INSTANCE(ops_cfg_bdb_mountfs)
{
    if(obj)
        free(obj);
}

