#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>

#include "iopcops_cfg_bdb_platform.h"

static void loadall()
{
    GET_INSTANCE(cfg_platform, bdb)->loadall();
}

static uint8_t is_host(uint8_t idx_cfg) 
{
    uint8_t result = 0;
    result = GET_INSTANCE(cfg_platform, bdb)->is_host(idx_cfg);
    return result;
}

static uint8_t is_init_console(uint8_t idx_cfg)
{
    uint8_t result = 0;
    result = GET_INSTANCE(cfg_platform, bdb)->is_init_console(idx_cfg);
    return result;
}

static uint16_t get_tty_name(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_tty_name(idx_cfg, cfg_val);

    return result;
}

static uint8_t is_init_zram_swap(uint8_t idx_cfg)
{
    uint8_t is_init_zram_swap = 0;

    is_init_zram_swap = GET_INSTANCE(cfg_platform, bdb)->is_init_zram_swap(idx_cfg);

    return is_init_zram_swap;
}

static uint16_t get_zram_disksize(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_zram_disksize(idx_cfg, cfg_val);

    return result;
}

static uint16_t get_platform_name(uint8_t idx_cfg, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_platform_name(idx_cfg, cfg_val);

    return result;
}

static uint8_t get_no_of_partition(uint8_t idx_cfg)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_no_partitions(idx_cfg);

    return result;
}

static uint8_t get_partition_fixed(uint8_t idx_cfg, uint8_t idx_part)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_partition_fixed(idx_cfg, idx_part);

    return result;
}

static uint8_t get_partition_enabled(uint8_t idx_cfg, uint8_t idx_part)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_partition_enabled(idx_cfg, idx_part);

    return result;
}

static void set_partition_enabled(uint8_t idx_cfg, uint8_t idx_part, uint8_t cfg_val)
{
    GET_INSTANCE(cfg_platform, bdb)->set_partition_enabled(idx_cfg, idx_part, cfg_val);
}

static uint16_t get_partition_src(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_partition_src(idx_cfg, idx_part, cfg_val);

    return result;
}

static void set_partition_src(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    GET_INSTANCE(cfg_platform, bdb)->set_partition_src(idx_cfg, idx_part, cfg_val);
}

static uint16_t get_partition_dst(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_partition_dst(idx_cfg, idx_part, cfg_val);

    return result;
}

static void set_partition_dst(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    GET_INSTANCE(cfg_platform, bdb)->set_partition_dst(idx_cfg, idx_part, cfg_val);
}

static uint16_t get_partition_type(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_partition_type(idx_cfg, idx_part, cfg_val);

    return result;
}

static void set_partition_type(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    GET_INSTANCE(cfg_platform, bdb)->set_partition_type(idx_cfg, idx_part, cfg_val);
}

static uint16_t get_partition_name(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_partition_name(idx_cfg, idx_part, cfg_val);

    return result;
}

static void set_partition_name(uint8_t idx_cfg, uint8_t idx_part, uint8_t* cfg_val)
{
    GET_INSTANCE(cfg_platform, bdb)->set_partition_name(idx_cfg, idx_part, cfg_val);
}

static uint8_t get_raid_size(uint8_t idx_cfg)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_raid_size(idx_cfg);

    return result;
}

static uint8_t get_raid_enabled(uint8_t idx_cfg, uint8_t idx_raid)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_raid_enabled(idx_cfg, idx_raid);

    return result;
}

static void set_raid_enabled(uint8_t idx_cfg, uint8_t idx_raid, uint8_t cfg_val)
{
    GET_INSTANCE(cfg_platform, bdb)->set_raid_enabled(idx_cfg, idx_raid, cfg_val);
}

static uint16_t get_raid_name(uint8_t idx_cfg, uint8_t idx_raid, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_raid_name(idx_cfg, idx_raid, cfg_val);

    return result;
}

static void set_raid_name(uint8_t idx_cfg, uint8_t idx_raid, uint8_t* cfg_val)
{
    GET_INSTANCE(cfg_platform, bdb)->set_raid_name(idx_cfg, idx_raid, cfg_val);
}

static uint16_t get_raid_type(uint8_t idx_cfg, uint8_t idx_raid, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_raid_type(idx_cfg, idx_raid, cfg_val);

    return result;
}

static void set_raid_type(uint8_t idx_cfg, uint8_t idx_raid, uint8_t* cfg_val)
{
    GET_INSTANCE(cfg_platform, bdb)->set_raid_type(idx_cfg, idx_raid, cfg_val);
}

static uint8_t get_raid_device_size(uint8_t idx_cfg, uint8_t idx_raid)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_raid_device_size(idx_cfg, idx_raid);

    return result;
}

static uint8_t get_raid_device_enabled(uint8_t idx_cfg, uint8_t idx_raid, uint8_t idx_raid_dev)
{
    uint8_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_raid_device_enabled(idx_cfg, idx_raid, idx_raid_dev);

    return result;
}

static void set_raid_device_enabled(uint8_t idx_cfg, uint8_t idx_raid, uint8_t idx_raid_dev, uint8_t cfg_val)
{
    GET_INSTANCE(cfg_platform, bdb)->set_raid_device_enabled(idx_cfg, idx_raid, idx_raid_dev, cfg_val);
}

static uint16_t get_raid_device_path(uint8_t idx_cfg, uint8_t idx_raid, uint8_t idx_raid_dev, uint8_t* cfg_val)
{
    uint16_t result = 0;

    result = GET_INSTANCE(cfg_platform, bdb)->get_raid_device_path(idx_cfg, idx_raid, idx_raid_dev, cfg_val);

    return result;
}

static void set_raid_device_path(uint8_t idx_cfg, uint8_t idx_raid, uint8_t idx_raid_dev, uint8_t* cfg_val)
{
    GET_INSTANCE(cfg_platform, bdb)->set_raid_device_path(idx_cfg, idx_raid, idx_raid_dev, cfg_val);
}

DEFINE_INSTANCE(cfg_platform, ifc);
DEFINE_GET_INSTANCE(cfg_platform, ifc)
{
    if(!obj) {
        obj = malloc(sizeof(struct ops_cfg_platform_t));
	obj->loadall = loadall;
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

DEFINE_DEL_INSTANCE(cfg_platform, ifc)
{
    if(obj)
        free(obj);
}

