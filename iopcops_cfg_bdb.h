#ifndef IOPCOPS_CFG_BDB_H
#define IOPCOPS_CFG_BDB_H

#if 0
#define DB_TYPE_STRING	"STRING"
#define DB_TYPE_UINT32	"UINT32"
#define DB_TYPE_BOOLEAN	"_BOOL_"

/*
#define DB_TYPE_UNKNOW	0x00
#define DB_TYPE_STRING	0x01
#define DB_TYPE_INT	0x02
#define DB_TYPE_BOOLEAN	0x03
*/
#define DB_MEDIA_UNKNOW	0x00
#define DB_MEDIA_FLASH	0x01
#define DB_MEDIA_RAM	0x02
#endif

#define GET_BOOLEAN(KEY)	GET_INSTANCE(ops_cfg_bdb)->get_boolean_flash(KEY)
#define GET_UINT32(KEY)		GET_INSTANCE(ops_cfg_bdb)->get_uint32_flash(KEY)
#define GET_STRING(KEY, VAL)	GET_INSTANCE(ops_cfg_bdb)->get_string_flash(KEY, VAL)

#define SET_BOOLEAN(KEY, VAL)	GET_INSTANCE(ops_cfg_bdb)->set_boolean_flash(KEY, VAL)
#define SET_UINT32(KEY, VAL)	GET_INSTANCE(ops_cfg_bdb)->set_uint32_flash(KEY, VAL)
#define SET_STRING(KEY, VAL)	GET_INSTANCE(ops_cfg_bdb)->set_string_flash(KEY, VAL)

struct ops_cfg_bdb_t {
    void (*init)(void);
    void (*save_cfgsdb2persist)();
    void (*restore_cfgsdb2default)();
    void (*save_persist2cfgsdb)();
    void (*set_value)(uint8_t*, uint8_t*, uint8_t*);
    uint16_t (*get_value)(uint8_t*, uint8_t*, uint8_t*);
    void (*show_all)(uint8_t* dbfile);

    uint8_t (*get_boolean_ram)(uint8_t* key);
    uint8_t (*get_boolean_flash)(uint8_t* key);
    void (*set_boolean_ram)(uint8_t* key, uint8_t val);
    void (*set_boolean_flash)(uint8_t* key, uint8_t val);

    uint32_t (*get_uint32_ram)(uint8_t* key);
    uint32_t (*get_uint32_flash)(uint8_t* key);
    void (*set_uint32_ram)(uint8_t* key, uint32_t val);
    void (*set_uint32_flash)(uint8_t* key, uint32_t val);

    uint16_t (*get_string_ram)(uint8_t* key, uint8_t* val);
    uint16_t (*get_string_flash)(uint8_t* key, uint8_t* val);
    void (*set_string_ram)(uint8_t* key, uint8_t* val);
    void (*set_string_flash)(uint8_t* key, uint8_t* val);
};

DEFINE_GET_INSTANCE(ops_cfg_bdb);
DEFINE_DEL_INSTANCE(ops_cfg_bdb);

#endif
