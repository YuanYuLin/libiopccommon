#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <db.h>

#include "iopcdefine.h"
#include "iopcops_cfg.h"
#include "iopcops_cfg_bdb.h"
#include "iopcops_misc.h"

#define CFGSDB_DEF	"/etc/iopc/cfgs.db"
#define CFGSDB_FLASH	"/persist/cfgsdb.flash"
#define CFGSDB_RAM	"/tmp/cfgsdb.ram"
//#define PERSIST_CFGSDB_FLASH	IOPC_PERSIST_CFGS_PATH
#define PERSIST_CFGSDB_FLASH	CFGSDB_FLASH

static void save_cfgsdb2persist(uint8_t* dbfile)
{
    GET_INSTANCE(misc, obj)->copy_file(CFGSDB_FLASH, PERSIST_CFGSDB_FLASH);
}

static void restore_cfgsdb2default()
{
    GET_INSTANCE(misc, obj)->copy_file(CFGSDB_DEF, CFGSDB_FLASH);
}

static void save_persist2cfgsdb()
{
    GET_INSTANCE(misc, obj)->copy_file(PERSIST_CFGSDB_FLASH, CFGSDB_FLASH);
}

static void init_db(void)
{
    if(GET_INSTANCE(misc, obj)->is_exist(CFGSDB_FLASH) < 0) {
	    printf("%s not exist\n", CFGSDB_FLASH);
        if(GET_INSTANCE(misc, obj)->is_exist(PERSIST_CFGSDB_FLASH) < 0) {
            //copy default cfg to CFGSDB_FLASH from /etc
            if(GET_INSTANCE(misc, obj)->is_exist(CFGSDB_DEF) < 0) {
                printf("default cfg not exist[%s]\n", CFGSDB_DEF);
            } else {
		printf("copy /etc/iopc/cfgs to /persist\n");
                restore_cfgsdb2default();
            }
	} else {
		printf("????\n");
            //copy cfg to CFGSDB_FLASH from /persist
            //save_persist2cfgsdb();
	}
    }
}

static void init_cfgsdb(uint8_t* dbfile)
{
    if(strcmp(CFGSDB_FLASH, dbfile) == 0) {
        init_db();
    }
}

static void set_value(uint8_t* dbfile, uint8_t* key, uint8_t* value)
{
    int ret;
    DB *dbp;
    DBT dbkey;
    DBT dbdata;

    init_cfgsdb(dbfile);

    if ((ret = db_create(&dbp, NULL, 0)) != 0) {
        printf("(%s)db_create error[%s]\n", __func__, db_strerror(ret));
	return ;
    }

    //if ((ret = dbp->open(dbp, NULL, dbfile, NULL, DB_BTREE, DB_CREATE, 0664)) != 0) 
    if ((ret = dbp->open(dbp, NULL, dbfile, NULL, DB_BTREE, DB_CREATE, 0664)) != 0) {
        printf("(%s)db_open error[%s]\n", __func__, db_strerror(ret));
    }

    memset(&dbkey, 0, sizeof(dbkey));
    memset(&dbdata, 0, sizeof(dbdata));

    dbkey.data = key;
    dbkey.size = strlen(key);

    dbdata.data = value;
    dbdata.size = strlen(value);

//    printf("set_value(): %d, %s, %d, %s\n", strlen(key), key, strlen(value), value);

    dbp->put(dbp, NULL, &dbkey, &dbdata, 0);

    dbp->close(dbp, 0);
}

static uint16_t get_value(uint8_t* dbfile, uint8_t* key, uint8_t* val)
{
    int ret;
    DB *dbp;
    DBT dbkey;
    DBT dbdata;
    uint16_t size = 0;

    init_cfgsdb(dbfile);

    if ((ret = db_create(&dbp, NULL, 0)) != 0) {
        printf("(%s)db_create error[%s]\n", __func__, db_strerror(ret));
        return 0;
    }

    if ((ret = dbp->open(dbp, NULL, dbfile, NULL, DB_BTREE, DB_CREATE, 0664)) != 0) {
        printf("(%s)db_open error[%s]\n", __func__, db_strerror(ret));
	return 0;
    }

    memset(&dbkey, 0, sizeof(dbkey));
    memset(&dbdata, 0, sizeof(dbdata));
//    printf("dbkey:%d\n", sizeof(dbkey));
    dbkey.data = key;
    dbkey.size = strlen(key);

    dbp->get(dbp, NULL, &dbkey, &dbdata, 0);

    memcpy(val, dbdata.data, dbdata.size);
    size = dbdata.size;
//    printf("get_value():[%d%s,%d:%s]\n", dbkey.size, dbkey.data, dbdata.size, dbdata.data);
//    printf("get_value():(%d, %s, %d, %s)\n", strlen(key), key, strlen(val), val);

    dbp->close(dbp, 0);
    return size;
}

static void show_all(uint8_t* dbfile)
{
    int ret = 0;
    DB *dbp;
    DBC *dbcp;
    DBT key;
    DBT data;
    uint8_t str[STR_LEN];

    if ((ret = db_create(&dbp, NULL, 0)) != 0) {
        printf("(%s)db_create error[%s]\n", __func__, db_strerror(ret));
	return;
    }

    if ((ret = dbp->open(dbp, NULL, dbfile, NULL, DB_BTREE, DB_CREATE, 0664)) != 0) {
        printf("(%s)db_open error[%s]\n", __func__, db_strerror(ret));
	return;
    }

    if ((ret = dbp->cursor(dbp, NULL, &dbcp, 0)) != 0) {
        printf("(%s)db_cursor error[%s]\n", __func__, db_strerror(ret));
	return;
    }

    memset(&key, 0, sizeof(key));
    memset(&data, 0, sizeof(data));

    while ((ret = dbcp->get(dbcp, &key, &data, DB_NEXT)) == 0) {
        memset(str, 0, STR_LEN);
	memcpy(str, key.data, key.size);
	printf("[%d]%s = ", key.size, str);
	memset(str, 0, STR_LEN);
	memcpy(str, data.data, data.size);
	printf("[%d]%s\n", data.size, str);
    }

    dbcp->close(dbcp);
    dbp->close(dbp, 0);
}

// ex: 0030008strplatform
//     string	: 6 bytes, type
//     0008	: 4 bytes, value string length
//     platform	: N bytes, value string
static uint16_t get_type_value(uint8_t* media, uint8_t* key, uint8_t* type, uint8_t* val)
{
    uint8_t val_len_str[5];
    uint8_t *val_str;
    uint16_t val_len = 0;
    val_str = malloc(MAX_STR_VAL);
    memset(val_str, 0, MAX_STR_VAL);
    memset(val_len_str, 0, sizeof(val_len_str));

    get_value(media, key, val_str);

    memcpy(type, &val_str[0], 6);
    memcpy(val_len_str, &val_str[6], 4);
    val_len = (uint16_t)strtol(val_len_str, NULL, 10);
    memcpy(val, &val_str[6+4], val_len);

    free(val_str);

    return val_len;
}

static void set_type_value(uint8_t* media, uint8_t* key, uint8_t* type, uint16_t val_len, uint8_t* val)
{
    uint8_t* val_str;
    val_str = malloc(MAX_STR_VAL);
    memset(val_str, 0, MAX_STR_VAL);
//    printf("%s():%s. %d, %s\n", __func__, type, val_len, val);
    sprintf(val_str, "%6s%04d%s", type, val_len, val);
//    printf("%s[%s]\n", media, val_str);

    set_value(media, key, val_str);
//    printf("Set value()\n");
}

static uint8_t get_boolean(uint8_t* media, uint8_t* key)
{
    uint8_t type[7];
    uint8_t *val_str;
    uint16_t val_len = 0;
    uint8_t val = 0;
    memset(type, 0, sizeof(type));
    val_str = malloc(MAX_STR_VAL);
    memset(val_str, 0, MAX_STR_VAL);
    val_len = get_type_value(media, key, &type[0], val_str);
    val = (uint8_t)strtol(val_str, NULL, 10);
    if(0)
        printf("%s() type:%s val:%s, len:%d\n", __func__, type, val_str, val_len);
    free(val_str);

//    printf("%s() %d, %d\n", __func__, val_len, val);

    return val;
}

static void set_boolean(uint8_t* media, uint8_t* key, uint8_t val)
{
    uint8_t *val_str;
    val_str = malloc(MAX_STR_VAL);
    memset(val_str, 0, MAX_STR_VAL);
    //printf("bool:%d\n", val);
    sprintf(val_str, "%d", val);
    //printf("%s():%s\n", __func__, val_str);
    set_type_value(media, key, DB_TYPE_BOOLEAN, strlen(val_str), val_str);
    free(val_str);
}

static uint8_t get_boolean_ram(uint8_t* key)
{
    return get_boolean(CFGSDB_RAM, key);
}

static uint8_t get_boolean_flash(uint8_t* key)
{
    return get_boolean(CFGSDB_FLASH, key);
}

static void set_boolean_ram(uint8_t* key, uint8_t val)
{
    //printf("%s(%d)\n", __func__, val);
    set_boolean(CFGSDB_RAM, key, val);
}

static void set_boolean_flash(uint8_t* key, uint8_t val)
{
    //printf("%s(%d)\n", __func__, val);
    set_boolean(CFGSDB_FLASH, key, val);
}

static uint32_t get_uint32(uint8_t* media, uint8_t* key)
{
    uint8_t type[7];
    uint8_t *val_str;
    uint16_t val_len;
    uint32_t val = 0;
    memset(type, 0, sizeof(type));
    val_str = malloc(MAX_STR_VAL);
    memset(val_str, 0, MAX_STR_VAL);
    val_len = get_type_value(media, key, &type[0], val_str);
    val = (uint32_t)strtoul(val_str, NULL, 10);
    free(val_str);

    if(0)
        printf("%s() %d\n", __func__, val_len);

    return val;
}

static void set_uint32(uint8_t* media, uint8_t* key, uint32_t val)
{
    uint8_t *val_str;
    val_str = malloc(MAX_STR_VAL);
    memset(val_str, 0, MAX_STR_VAL);
    sprintf(val_str, "%d", val);
    set_type_value(media, key, DB_TYPE_UINT32, strlen(val_str), val_str);
    free(val_str);
}

static uint32_t get_uint32_ram(uint8_t* key)
{
    return get_uint32(CFGSDB_RAM, key);
}

static uint32_t get_uint32_flash(uint8_t* key)
{
    return get_uint32(CFGSDB_FLASH, key);
}

static void set_uint32_ram(uint8_t* key, uint32_t val)
{
    set_uint32(CFGSDB_RAM, key, val);
}

static void set_uint32_flash(uint8_t* key, uint32_t val)
{
    set_uint32(CFGSDB_FLASH, key, val);
}

static uint16_t get_string(uint8_t* media, uint8_t* key, uint8_t* val)
{
    uint8_t type[7];
    uint16_t val_len;
    memset(type, 0, sizeof(type));
    val_len = get_type_value(media, key, &type[0], val);

    return val_len;
}

static void set_string(uint8_t* media, uint8_t* key, uint8_t* val)
{
    set_type_value(media, key, DB_TYPE_STRING, strlen(val), val);	
}

static uint16_t get_string_ram(uint8_t* key, uint8_t* val)
{
    return get_string(CFGSDB_RAM, key, val);
}

static uint16_t get_string_flash(uint8_t* key, uint8_t* val)
{
    return get_string(CFGSDB_FLASH, key, val);
}

static void set_string_ram(uint8_t* key, uint8_t* val)
{
    set_string(CFGSDB_RAM, key, val);
}

static void set_string_flash(uint8_t* key, uint8_t* val)
{
    set_string(CFGSDB_FLASH, key, val);
}

//static struct ops_cfg_bdb_t* obj = NULL;

DEFINE_INSTANCE(cfg_bdb, ifc);
DEFINE_GET_INSTANCE(cfg_bdb, ifc)
{
    if(!obj) {
        obj = malloc(sizeof(struct ops_cfg_bdb_t));
	obj->init = init_db;
	obj->save_cfgsdb2persist = save_cfgsdb2persist;
	obj->restore_cfgsdb2default = restore_cfgsdb2default;
	obj->save_persist2cfgsdb = save_persist2cfgsdb;
	obj->get_value = get_value;
	obj->set_value = set_value;
	obj->show_all = show_all;
	obj->get_boolean_ram = get_boolean_ram;
	obj->get_boolean_flash = get_boolean_flash;
	obj->set_boolean_ram = set_boolean_ram;
	obj->set_boolean_flash = set_boolean_flash;
	obj->get_uint32_ram = get_uint32_ram;
	obj->get_uint32_flash = get_uint32_flash;
	obj->set_uint32_ram = set_uint32_ram;
	obj->set_uint32_flash = set_uint32_flash;
	obj->get_string_ram = get_string_ram;
	obj->get_string_flash = get_string_flash;
	obj->set_string_ram = set_string_ram;
	obj->set_string_flash = set_string_flash;
    }

    return obj;
}

DEFINE_DEL_INSTANCE(cfg_bdb, ifc)
{
    if(obj)
        free(obj);
}

