#ifndef CLIENT_DB_H
#define CLIENT_DB_H

#include "iopc_dbinfo.h"

struct client_db_t {
    uint8_t (*get_bool_flash)(uint8_t* key);
    uint8_t (*get_bool_ram)(uint8_t* key);
    uint8_t (*set_bool_flash)(uint8_t* key, uint8_t val);
    uint8_t (*set_bool_ram)(uint8_t* key, uint8_t val);
    uint32_t (*get_uint32_flash)(uint8_t* key);
    uint32_t (*get_uint32_ram)(uint8_t* key);
    uint8_t (*set_uint32_flash)(uint8_t* key, uint32_t val);
    uint8_t (*set_uint32_ram)(uint8_t* key, uint32_t val);
    uint16_t (*get_string_flash)(uint8_t* key, uint8_t* val);
    uint16_t (*get_string_ram)(uint8_t* key, uint8_t* val);
    uint8_t (*set_string_flash)(uint8_t* key, uint8_t* val);
    uint8_t (*set_string_ram)(uint8_t* key, uint8_t* val);
    uint8_t (*save2persist)(void);
    uint8_t (*restore2default)(void);
};

DEFINE_GET_INSTANCE(client_db);
DEFINE_DEL_INSTANCE(client_db);

#endif
