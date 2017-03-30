#ifndef IOPCOPS_CFG_JSON_H
#define IOPCOPS_CFG_JSON_H

struct cfg_json_t {
    struct json_object *data;
};

struct ops_cfg_json_t {
    int (*open)(uint8_t *cfg_file, struct cfg_json_t* cfg);
    int (*close)(struct cfg_json_t* cfg);
    void (*show_all)(struct cfg_json_t* cfg);
    void (*show)(struct cfg_json_t* cfg, char* index_key);
    struct json_object* (*get_raw)(struct cfg_json_t* cfg, char* index_key);
    uint16_t (*get_string)(uint8_t* err_code, struct cfg_json_t* cfg, char* index_key, uint8_t* cfg_val);
    int (*get_int)(uint8_t* err_code, struct cfg_json_t* cfg, char* index_key);
    double (*get_double)(uint8_t* err_code, struct cfg_json_t* cfg, char* index_key);
    int (*get_boolean)(uint8_t* err_code, struct cfg_json_t* cfg, char* index_key);
    int (*get_array_size)(uint8_t* err_code, struct cfg_json_t* cfg, char* index_key);
};

DEFINE_GET_INSTANCE(dao, json);
DEFINE_DEL_INSTANCE(dao, json);

#endif
