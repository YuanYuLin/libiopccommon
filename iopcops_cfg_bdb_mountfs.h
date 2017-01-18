#ifndef IOPCOPS_CFG_BDB_MOUNTFS_H
#define IOPCOPS_CFG_BDB_MOUNTFS_H

struct ops_cfg_bdb_mountfs_t {
    void (*loadall)(void);
    uint32_t (*get_no_of_size)();
    uint16_t (*get_name)(uint8_t idx_cfg, uint8_t* cfg_val);
    uint8_t (*is_fixed)(uint8_t idx_cfg);
    uint16_t (*get_dst)(uint8_t idx_cfg, uint8_t* cfg_val);
    uint16_t (*get_src)(uint8_t idx_cfg, uint8_t* cfg_val);
};

DEFINE_GET_INSTANCE(ops_cfg_bdb_mountfs);
DEFINE_DEL_INSTANCE(ops_cfg_bdb_mountfs);

#endif
