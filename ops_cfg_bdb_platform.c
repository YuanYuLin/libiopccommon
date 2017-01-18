#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>

#include "iopcdefine.h"
#include "iopcops_cfg_bdb.h"
#include "iopcops_cfg_bdb_platform.h"

#define IS_HOST			"platform.cfg[%d].is_host"
#define IS_INIT_CONSOLE		"platform.cfg[%d].is_init_console"
#define TTY_NAME		"platform.cfg[%d].tty_name"
#define IS_INIT_ZRAM_SWAP	"platform.cfg[%d].is_init_zram_swap"
#define ZRAM_DISKSIZE		"platform.cfg[%d].zram_disksize"
#define PLATFORM_NAME		"platform.cfg[%d].platform_name"

#define RAID_SIZE		"platform.cfg[%d].raid.size"
#define RAID_NAME		"platform.cfg[%d].raid[%d].name"
#define RAID_TYPE		"platform.cfg[%d].raid[%d].type"
#define RAID_ENABLED		"platform.cfg[%d].raid[%d].enabled"
#define RAID_DEVICE_SIZE	"platform.cfg[%d].raid[%d].device.size"
#define RAID_DEVICE_ENABLED	"platform.cfg[%d].raid[%d].device[%d].enabled"
#define RAID_DEVICE_PATH	"platform.cfg[%d].raid[%d].device[%d].path"

#define PARTITION_SIZE		"platform.cfg[%d].partition.size"
#define PARTITION_SRC		"platform.cfg[%d].partition[%d].src"
#define PARTITION_DST		"platform.cfg[%d].partition[%d].dst"
#define PARTITION_TYPE		"platform.cfg[%d].partition[%d].type"
#define PARTITION_NAME		"platform.cfg[%d].partition[%d].name"
#define PARTITION_FIXED		"platform.cfg[%d].partition[%d].fixed"
#define PARTITION_ENABLED	"platform.cfg[%d].partition[%d].enabled"

static void loadall()
{
    GET_INSTANCE(ops_cfg_bdb)->init();
}

static uint8_t is_host(uint8_t idx_cfg) 
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, IS_HOST, idx_cfg);

    result = GET_BOOLEAN(cfg_str);

    if(result)
        return 1;
    return 0;
}

static uint8_t is_init_console(uint8_t idx_cfg)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, IS_INIT_CONSOLE, idx_cfg);
    result = GET_BOOLEAN(cfg_str);

    if(result)
        return 1;
    return 0;
}

static uint16_t get_tty_name(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, TTY_NAME, idx_cfg);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
	    printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static uint8_t is_init_zram_swap(uint8_t idx_cfg)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, IS_INIT_ZRAM_SWAP, idx_cfg);
    result = GET_BOOLEAN(cfg_str);

    if(result)
        return 1;
    return 0;
}

static uint16_t get_zram_disksize(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, ZRAM_DISKSIZE, idx_cfg);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
	    printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));
    return result;
}

static uint16_t get_platform_name(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PLATFORM_NAME, idx_cfg);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
	    printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static uint8_t get_no_of_partition(uint8_t idx_cfg)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PARTITION_SIZE, idx_cfg);
    result = GET_UINT32(cfg_str);

    return result;
}

static uint8_t get_partition_fixed(uint8_t idx_cfg, uint8_t idx_part)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PARTITION_FIXED, idx_cfg, idx_part);
    result = GET_BOOLEAN(cfg_str);

    if(result)
        return 1;
    return 0;
}

static uint8_t get_partition_enabled(uint8_t idx_cfg, uint8_t idx_part)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PARTITION_ENABLED, idx_cfg, idx_part);
    result = GET_BOOLEAN(cfg_str);

    if(result)
        return 1;
    return 0;
}

static void set_partition_enabled(uint8_t idx_cfg, uint8_t idx_part, uint8_t cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PARTITION_ENABLED, idx_cfg, idx_part);

    SET_BOOLEAN(cfg_str, cfg_val);
}

static uint16_t get_partition_src(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PARTITION_SRC, idx_cfg, idx_part);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
	    printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static void set_partition_src(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PARTITION_SRC, idx_cfg, idx_part);

    SET_STRING(cfg_str, cfg_val);
}

static uint16_t get_partition_dst(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PARTITION_DST, idx_cfg, idx_part);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
	    printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static void set_partition_dst(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PARTITION_DST, idx_cfg, idx_part);

    SET_STRING(cfg_str, cfg_val);
}

static uint16_t get_partition_type(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PARTITION_TYPE, idx_cfg, idx_part);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
	    printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static void set_partition_type(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PARTITION_TYPE, idx_cfg, idx_part);

    SET_STRING(cfg_str, cfg_val);
}

static uint16_t get_partition_name(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PARTITION_NAME, idx_cfg, idx_part);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
	    printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static void set_partition_name(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, PARTITION_NAME, idx_cfg, idx_part);

    SET_STRING(cfg_str, cfg_val);
}

static uint8_t get_raid_size(uint8_t idx_cfg)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, RAID_SIZE, idx_cfg);
    result = GET_UINT32(cfg_str);
    printf("%s:%s:%d\n", __func__, cfg_str, result);

    return result;
}

static uint8_t get_raid_enabled(uint8_t idx_cfg, uint8_t idx_raid)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, RAID_ENABLED, idx_cfg, idx_raid);
    result = GET_BOOLEAN(cfg_str);

    if(result)
        return 1;
    return 0;
}

static void set_raid_enabled(uint8_t idx_cfg, uint8_t idx_raid, uint8_t cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, RAID_ENABLED, idx_cfg, idx_raid);

    SET_BOOLEAN(cfg_str, cfg_val);
}

static uint16_t get_raid_name(uint8_t idx_cfg, uint8_t idx_raid, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, RAID_NAME, idx_cfg, idx_raid);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
	    printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static void set_raid_name(uint8_t idx_cfg, uint8_t idx_raid, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, RAID_NAME, idx_cfg, idx_raid);

    SET_STRING(cfg_str, cfg_val);
}

static uint16_t get_raid_type(uint8_t idx_cfg, uint8_t idx_raid, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, RAID_TYPE, idx_cfg, idx_raid);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
	    printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static void set_raid_type(uint8_t idx_cfg, uint8_t idx_raid, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, RAID_TYPE, idx_cfg, idx_raid);

    SET_STRING(cfg_str, cfg_val);
}

static uint8_t get_raid_device_size(uint8_t idx_cfg, uint8_t idx_raid)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, RAID_DEVICE_SIZE, idx_cfg, idx_raid);
    result = GET_UINT32(cfg_str);

    return result;
}

static uint8_t get_raid_device_enabled(uint8_t idx_cfg, uint8_t idx_raid, uint8_t idx_raid_dev)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint8_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, RAID_DEVICE_ENABLED, idx_cfg, idx_raid, idx_raid_dev);
    result = GET_BOOLEAN(cfg_str);

    if(result)
        return 1;
    return 0;
}

static void set_raid_device_enabled(uint8_t idx_cfg, uint8_t idx_raid, uint8_t idx_raid_dev, uint8_t cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, RAID_DEVICE_ENABLED, idx_cfg, idx_raid, idx_raid_dev);

    SET_BOOLEAN(cfg_str, cfg_val);
}

static uint16_t get_raid_device_path(uint8_t idx_cfg, uint8_t idx_raid, uint8_t idx_raid_dev, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    uint16_t result = 0;
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, RAID_DEVICE_PATH, idx_cfg, idx_raid, idx_raid_dev);
    result = GET_STRING(cfg_str, cfg_val);
    if(result != strlen(cfg_val))
	    printf("[%s]error len(%d,%d)\n", __func__, result, strlen(cfg_val));

    return result;
}

static void set_raid_device_path(uint8_t idx_cfg, uint8_t idx_raid, uint8_t idx_raid_dev, uint8_t* cfg_val)
{
    uint8_t cfg_str[STR_LEN] = {0};
    memset(cfg_str, 0, STR_LEN);
    sprintf(cfg_str, RAID_DEVICE_PATH, idx_cfg, idx_raid, idx_raid_dev);

    SET_STRING(cfg_str, cfg_val);
}

//static struct ops_cfg_bdb_platform_t* obj = NULL;

DEFINE_INSTANCE(ops_cfg_bdb_platform);
DEFINE_GET_INSTANCE(ops_cfg_bdb_platform)
{
//    struct ops_cfg_platform_t* obj = NULL;
    if(!obj) {
        obj = malloc(sizeof(struct ops_cfg_bdb_platform_t));
	obj->loadall = loadall;
//	obj->get_cfg_idx = get_cfg_idx;
//	obj->set_cfg_idx = set_cfg_idx;
	obj->is_host = is_host;
	obj->is_init_console = is_init_console;
	obj->is_init_zram_swap = is_init_zram_swap;
	obj->get_zram_disksize = get_zram_disksize;
	obj->get_tty_name = get_tty_name;
	obj->get_platform_name = get_platform_name;
	obj->get_no_partitions = get_no_of_partition;
	obj->get_partition_fixed = get_partition_fixed;

	obj->get_partition_src = get_partition_src;
	obj->get_partition_dst = get_partition_dst;
	obj->get_partition_type = get_partition_type;
	obj->get_partition_name = get_partition_name;
	obj->get_partition_enabled = get_partition_enabled;

	obj->set_partition_src = set_partition_src;
	obj->set_partition_dst = set_partition_dst;
	obj->set_partition_type = set_partition_type;
	obj->set_partition_name = set_partition_name;
	obj->set_partition_enabled = set_partition_enabled;

	obj->get_raid_size = get_raid_size;
	obj->get_raid_device_size = get_raid_device_size;

	obj->get_raid_enabled = get_raid_enabled;
	obj->get_raid_name = get_raid_name;
	obj->get_raid_type = get_raid_type;
	obj->get_raid_device_enabled = get_raid_device_enabled;
	obj->get_raid_device_path = get_raid_device_path;

	obj->set_raid_enabled = set_raid_enabled;
	obj->set_raid_name = set_raid_name;
	obj->set_raid_type = set_raid_type;
	obj->set_raid_device_enabled = set_raid_device_enabled;
	obj->set_raid_device_path = set_raid_device_path;
    }

    return obj;
}

DEFINE_DEL_INSTANCE(ops_cfg_bdb_platform)
{
    if(obj)
        free(obj);
}

