#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <json.h>
#include <json_object.h>

#include "iopcdefine.h"
#include "iopcops_cfg_json.h"

static int open_cfg(uint8_t *cfg_file, struct cfg_json_t* cfg)
{
    cfg->data = json_object_from_file((const char*)cfg_file);
    return 0;
}

static int close_cfg(struct cfg_json_t* cfg)
{
    return 0;
}

static void show_next_obj(char *key_str, struct json_object *obj_val);

static void get_type_obj(char*key_str, struct json_object *obj_val)
{
    char tmp_str[STR_LEN]={0};
    json_object_object_foreach(obj_val, tmpkey, tmpval) {
        sprintf(tmp_str, "%s.%s", key_str, tmpkey);
        show_next_obj(tmp_str, tmpval);
    }
}

static void get_type_array(char *key_str, struct json_object *obj_val)
{
    struct json_object *ele_obj;
    int array_len = 0;
    int i = 0;
    char tmp_str[STR_LEN]={0};
    array_len = json_object_array_length(obj_val);
    for(i=0; i<array_len; i++) {
        ele_obj = json_object_array_get_idx(obj_val, i);
        sprintf(tmp_str, "%s[%d]", key_str, i);
        show_next_obj(tmp_str, ele_obj);
    }
}

static void show_next_obj(char *key_str, struct json_object *obj_val)
{
    enum json_type type;
    type = json_object_get_type(obj_val);

    switch(type){
    case json_type_null:
        printf("%s=%s\n", key_str, "NULL");
    break;
    case json_type_boolean:
        printf("%s=%d\n", key_str, json_object_get_boolean(obj_val));
    break;
    case json_type_double:
        printf("%s=%f\n", key_str, json_object_get_double(obj_val));
    break;
    case json_type_int:
        printf("%s=%d\n", key_str, json_object_get_int(obj_val));
    break;
    case json_type_object:
        get_type_obj(key_str, obj_val);
    break;
    case json_type_array:
        get_type_array(key_str, obj_val);
    break;
    case json_type_string:
        printf("%s=%s\n", key_str, json_object_get_string(obj_val));
    break;
    default:
        printf("JSON type error\n");
    break;
    }
}

static void show_all_cfg(struct cfg_json_t* cfg)
{
    json_object_object_foreach(cfg->data, obj_key, obj_val) {
        show_next_obj(obj_key, obj_val);
    }
}

static struct json_object* search_next_obj(char *key_str, struct json_object *obj_val, char* index_key);

static struct json_object* parse_value_obj_by_query_obj(char *key_str, struct json_object *obj_val, char* index_key)
{
    char tmp_str[STR_LEN]={0};
    struct json_object *ele_obj = NULL;
    json_object_object_foreach(obj_val, tmpkey, tmpval) {
        sprintf(tmp_str, "%s.%s", key_str, tmpkey);
        if(strcmp(tmp_str, index_key) == 0) {
            return tmpval;
	}
	//printf("obj cmp : %s, %s\n", tmp_str, index_key);
	ele_obj = search_next_obj(tmp_str, tmpval, index_key);
	if(ele_obj != NULL)
            return ele_obj;
    }
    return NULL;
}

static struct json_object* parse_value_array_by_query_obj(char *key_str, struct json_object *obj_val, char* index_key)
{
    struct json_object *ele_obj;
    int array_len = 0;
    int i = 0;
    char tmp_str[STR_LEN]={0};
    array_len = json_object_array_length(obj_val);
    for(i=0; i<array_len; i++) {
        ele_obj = json_object_array_get_idx(obj_val, i);
        sprintf(tmp_str, "%s[%d]", key_str, i);
        if(strcmp(tmp_str, index_key) == 0){
            return ele_obj;
        }
	//printf("array cmd : %s, %s\n", tmp_str, index_key);
        ele_obj = search_next_obj(tmp_str, ele_obj, index_key);
	if(ele_obj != NULL)
            return ele_obj;

    }
    return NULL;
}

static struct json_object* search_next_obj(char *key_str, struct json_object *obj_val, char* index_key)
{
    enum json_type type;
    char tmp_str[STR_LEN]={0};

    type = json_object_get_type(obj_val);
    //printf("last : %d, %s\n", type, key_str);
    switch(type) {
    case json_type_object:
        sprintf(tmp_str, "%s", key_str);
	if(strcmp(tmp_str, index_key) == 0) {
            return obj_val;
	}
	return parse_value_obj_by_query_obj(key_str, obj_val, index_key);
    break;
    case json_type_array:
        sprintf(tmp_str, "%s", key_str);
	if(strcmp(tmp_str, index_key) == 0) {
            return obj_val;
	}
	return parse_value_array_by_query_obj(key_str, obj_val, index_key);
    break;
    case json_type_null:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, index_key) == 0) {
            return obj_val;
        }
    break;
    case json_type_boolean:
        sprintf(tmp_str, "%s", key_str);
	if(strcmp(tmp_str, index_key) == 0) {
            return obj_val;
	}
    break;
    case json_type_double:
        sprintf(tmp_str, "%s", key_str);
	if(strcmp(tmp_str, index_key) == 0) {
            return obj_val;
	}
    break;
    case json_type_int:
        sprintf(tmp_str, "%s", key_str);
	if(strcmp(tmp_str, index_key) == 0) {
            return obj_val;
	}
    break;
    case json_type_string:
        sprintf(tmp_str, "%s", key_str);
	if(strcmp(tmp_str, index_key) == 0) {
            return obj_val;
	}
    break;
    }
    return NULL;
}

static struct json_object* get_cfg(struct cfg_json_t* cfg, char* index_key)
{
#if 0
    struct json_object* result = NULL;

    json_object_object_foreach(cfg->data, obj_key, obj_val) {
	    printf("Key: %s\n", obj_key);
        result = search_next_obj(obj_key, obj_val, index_key);
	if(result != NULL) {
		printf("get result\n");
            return result;
	}
    }
    printf("return NULL\n");
    return NULL;
#else
    struct json_object* result = NULL;
    json_object_object_foreach(cfg->data, obj_key, obj_val) {
        result = search_next_obj(obj_key, obj_val, index_key);
	if(result != NULL) {
            return result;
	}
    }
    return NULL;
#endif
}
/*
static json_object* set_cfg(struct cfg_json_t* cfg, char* index_key)
{
    struct json_object* result = NULL;
    json_object_object_foreach(cfg->data, obj_key, obj_val) {
        result = search_next_obj(obj_key, obj_val, index_key);
    }

    return result;
}
*/
static int check_json_type(struct json_object* obj, enum json_type obj_type)
{
    enum json_type type;
    if(obj != NULL) {
        type = json_object_get_type(obj);
        if(type != obj_type){
            return -1;
	}
	return 0;
    }
    return -1;
}

static int get_cfg_array_size(uint8_t* err_code, struct cfg_json_t* cfg, char* index_key)
{
    struct json_object* result = NULL;
    *err_code = 0;
    result = get_cfg(cfg, index_key);

    if(!check_json_type(result, json_type_array)){
	return json_object_array_length(result);
    }

    *err_code = 1;
    return 0;
}
/*
static struct array_list* get_cfg_array(uint8_t* err_code, struct cfg_json_t* cfg, char* index_key)
{
    struct json_object* result = NULL;
    *err_code = 0;
    result = get_cfg(cfg, index_key);
    if(!check_json_type(result, json_type_array)){
        return json_object_get_array(result);
    }

    *err_code = 1;
    return NULL;
}
*/
static uint16_t get_cfg_string(uint8_t* err_code, struct cfg_json_t* cfg, char* index_key, uint8_t* cfg_val)
{
    struct json_object* result = NULL;
    *err_code = 0;
    result = get_cfg(cfg, index_key);

    //printf("type:%d, %s\n", json_object_get_type(result), json_object_get_string(result));
    if(!check_json_type(result, json_type_string)){
        cfg_val = (uint8_t*)json_object_get_string(result);
	return (uint16_t)strlen(cfg_val);
    }

    cfg_val = "";
    *err_code = 1;
    return 0;
}
/*
static void set_cfg_string(uint8_t* err_code, struct cfg_json_t* cfg, char* index_key)
{
    struct json_object* result = NULL;
    *err_code = 0;
    result = get_cfg(cfg, index_key);

    if(!check_json_type(result, json_type_string)){
        (char*)json_object_get_string(result);
    }

    *err_code = 1;
}
*/
static int get_cfg_int(uint8_t* err_code, struct cfg_json_t* cfg, char* index_key)
{
    struct json_object* result = NULL;
    *err_code = 0;
    result = get_cfg(cfg, index_key);

    if(!check_json_type(result, json_type_int)){
        return json_object_get_int(result);
    }

    *err_code = 1;
    return 0;
}

static double get_cfg_double(uint8_t* err_code, struct cfg_json_t* cfg, char* index_key)
{
    struct json_object* result = NULL;
    *err_code = 0;
    result = get_cfg(cfg, index_key);

    if(!check_json_type(result, json_type_double)){
	return json_object_get_double(result);
    }

    *err_code = 1;
    return 0;
}

static int get_cfg_boolean(uint8_t* err_code, struct cfg_json_t* cfg, char* index_key)
{
    struct json_object* result = NULL;
    *err_code = 0;
    result = get_cfg(cfg, index_key);

    if(!check_json_type(result, json_type_boolean)){
        return json_object_get_boolean(result);
    }

    *err_code = 1;
    return 0;
}

static void show_cfg(struct cfg_json_t* cfg, char* index_key)
{
    int isFound = 0;
    enum json_type type;
    struct json_object* result = NULL;
    result = get_cfg(cfg, index_key);
    if(result != NULL) {
        isFound = 1;
    }
#if 0
    json_object_object_foreach(cfg->data, obj_key, obj_val) {
        result = search_next_obj(obj_key, obj_val, index_key);
	if(result != NULL) {
            printf("found \n");
	    isFound = 1;
            break;
	}
    }
#endif

    if(isFound) {
        type = json_object_get_type(result);
        switch(type){
        case json_type_null:
            printf("%s", "NULL");
        break;
        case json_type_boolean:
            printf("%d", json_object_get_boolean(result));
        break;
        case json_type_double:
            printf("%f", json_object_get_double(result));
        break;
        case json_type_int:
            printf("%d", json_object_get_int(result));
        break;
        case json_type_string:
            printf("%s", json_object_get_string(result));
        break;
        case json_type_object:
        case json_type_array:
        default:
            printf("this is obj type \n");
        break;
        }
    }
}

//static struct ops_cfg_json_t* obj = NULL;

DEFINE_INSTANCE(ops_cfg_json);
DEFINE_GET_INSTANCE(ops_cfg_json)
{
    if(!obj) {
        obj = malloc(sizeof(struct ops_cfg_json_t));
        obj->open = open_cfg;
	obj->close = close_cfg;
	obj->show_all = show_all_cfg;
	obj->show = show_cfg;
	obj->get_raw = get_cfg;
	obj->get_string = get_cfg_string;
	obj->get_int = get_cfg_int;
	obj->get_boolean = get_cfg_boolean;
	obj->get_double = get_cfg_double;
	obj->get_array_size = get_cfg_array_size;
	//obj->get_array = get_cfg_array;
    }

    return obj;
}

DEFINE_DEL_INSTANCE(ops_cfg_json)
{
    if(obj)
        free(obj);
}

