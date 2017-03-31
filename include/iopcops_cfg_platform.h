#ifndef IOPCCFG_PLATFORM_H
#define IOPCCFG_PLATFORM_H

#include "iopcdefine.h"

struct ops_cfg_platform_t {
    void        (*loadall)(void);
//    uint8_t     (*get_cfg_idx)(void);
//    void        (*set_cfg_idx)(uint8_t);
    uint16_t    (*get_platform_name)(uint8_t idx_cfg, uint8_t* cfg_val);
    uint16_t    (*get_tty_name)(uint8_t idx_cfg, uint8_t* cfg_val);
    uint8_t     (*is_init_console)(uint8_t idx_cfg);
    uint8_t	(*is_init_zram_swap)(uint8_t idx_cfg);
    uint16_t	(*get_zram_disksize)(uint8_t idx_cfg, uint8_t* cfg_val);
    uint8_t     (*is_host)(uint8_t idx_cfg);
    uint8_t     (*get_no_partitions)(uint8_t idx_cfg);
    uint8_t	(*get_partition_fixed)(uint8_t idx_cfg, uint8_t);

    uint16_t    (*get_partition_src)(uint8_t idx_cfg, uint8_t, uint8_t*);
    uint16_t    (*get_partition_dst)(uint8_t idx_cfg, uint8_t, uint8_t*);
    uint16_t    (*get_partition_type)(uint8_t idx_cfg, uint8_t, uint8_t*);
    uint16_t    (*get_partition_name)(uint8_t idx_cfg, uint8_t, uint8_t*);
    uint8_t	(*get_partition_enabled)(uint8_t idx_cfg, uint8_t);

    void        (*set_partition_src)(uint8_t idx_cfg, uint8_t, uint8_t*);
    void        (*set_partition_dst)(uint8_t idx_cfg, uint8_t, uint8_t*);
    void        (*set_partition_type)(uint8_t idx_cfg, uint8_t, uint8_t*);
    void        (*set_partition_name)(uint8_t idx_cfg, uint8_t, uint8_t*);
    void	(*set_partition_enabled)(uint8_t idx_cfg, uint8_t, uint8_t);

    uint8_t	(*get_raid_size)(uint8_t idx_cfg);

    uint8_t	(*get_raid_enabled)(uint8_t idx_cfg, uint8_t idx_raid);
    uint16_t	(*get_raid_name)(uint8_t idx_cfg, uint8_t idx_raid, uint8_t* cfg_val);
    uint16_t	(*get_raid_type)(uint8_t idx_cfg, uint8_t idx_raid, uint8_t* cfg_val);
    uint8_t	(*get_raid_device_size)(uint8_t idx_cfg, uint8_t idx_raid);
    uint8_t	(*get_raid_device_enabled)(uint8_t idx_cfg, uint8_t idx_raid, uint8_t idx_raid_dev);
    uint16_t	(*get_raid_device_path)(uint8_t idx_cfg, uint8_t, uint8_t, uint8_t* );

    void	(*set_raid_enabled)(uint8_t idx_cfg, uint8_t idx_raid, uint8_t);
    void	(*set_raid_name)(uint8_t idx_cfg, uint8_t idx_raid, uint8_t*);
    void	(*set_raid_type)(uint8_t idx_cfg, uint8_t idx_raid, uint8_t*);
    void	(*set_raid_device_enabled)(uint8_t idx_cfg, uint8_t, uint8_t, uint8_t);
    void	(*set_raid_device_path)(uint8_t idx_cfg, uint8_t, uint8_t, uint8_t*);
};

DEFINE_GET_INSTANCE(cfg_platform, ifc);
DEFINE_DEL_INSTANCE(cfg_platform, ifc);

#define GET_INSTANCE_CFG_PLATFORM() GET_INSTANCE(cfg_platform, ifc)

#endif
