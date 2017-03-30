#ifndef IOPCCMD_DB_H
#define IOPCCMD_DB_H

struct req_dbsetbool_t {
    uint8_t key_len;
    uint8_t key[STR_LEN];
    uint8_t val;
}__PACKED__;
struct res_dbsetbool_t {
    uint8_t status;
}__PACKED__;

struct req_dbgetbool_t {
    uint8_t key_len;
    uint8_t key[STR_LEN];
}__PACKED__;
struct res_dbgetbool_t {
    uint8_t status;
    uint8_t val;
}__PACKED__;

struct req_dbsetuint32_t {
    uint8_t key_len;
    uint8_t key[STR_LEN];
    uint32_t val;
}__PACKED__;
struct res_dbsetuint32_t {
    uint8_t status;
}__PACKED__;

struct req_dbgetuint32_t {
    uint8_t key_len;
    uint8_t key[STR_LEN];
}__PACKED__;
struct res_dbgetuint32_t {
    uint8_t status;
    uint32_t val;
}__PACKED__;

struct req_dbsetstring_t {
    uint8_t key_len;
    uint8_t key[STR_LEN];
    uint16_t val_len;
    uint8_t val[MAX_STR_VAL];
}__PACKED__;
struct res_dbsetstring_t {
    uint8_t status;
}__PACKED__;

struct req_dbgetstring_t {
    uint8_t key_len;
    uint8_t key[STR_LEN];
}__PACKED__;
struct res_dbgetstring_t {
    uint8_t status;
    uint16_t val_len;
    uint8_t val[MAX_STR_VAL];
}__PACKED__;

struct req_save2persist_t {
}__PACKED__;
struct res_save2persist_t {
    uint8_t status;
}__PACKED__;

struct req_restore2default_t {
}__PACKED__;
struct res_restore2default_t {
    uint8_t status;
}__PACKED__;

#endif

