#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>

#include "iopcdefine.h"
#include "iopcops_cfg.h"
#include "iopcops_cfg_status.h"
#include "iopcops_cfg_bdb.h"
#include "iopcops_cfg_bdb_status.h"

#define SERVICE_STATUS	"status.service"
#define SERVICE_STATUS_UNKNOW		0x00
#define SERVICE_STATUS_STARTING		0x01
#define SERVICE_STATUS_STARTED		0x02
#define SERVICE_STATUS_STOPING		0x03
#define SERVICE_STATUS_STOPED		0x04

#define SET_SERVICE_STARTING(NAME)	GET_INSTANCE(cfg_bdb, ifc)->set_uint32_ram(NAME, SERVICE_STATUS_STARTING)
#define SET_SERVICE_STOPING(NAME)	GET_INSTANCE(cfg_bdb, ifc)->set_uint32_ram(NAME, SERVICE_STATUS_STOPING)
#define SET_SERVICE_STARTED(NAME)	GET_INSTANCE(cfg_bdb, ifc)->set_uint32_ram(NAME, SERVICE_STATUS_STARTED)
#define SET_SERVICE_STOPED(NAME)	GET_INSTANCE(cfg_bdb, ifc)->set_uint32_ram(NAME, SERVICE_STATUS_STOPED)
#define GET_SERVICE_STATUS(NAME)	GET_INSTANCE(cfg_bdb, ifc)->get_uint32_ram(NAME)

#define PROGRESS_STATUS	"status.progress"
#define GET_PROGRESS_STATUS(NAME)	GET_INSTANCE(cfg_bdb, ifc)->get_uint32_ram(NAME)
#define SET_PROGRESS_STATUS(NAME, STATUS)	GET_INSTANCE(cfg_bdb, ifc)->set_uint32_ram(NAME, STATUS)

/*
#define SET_SERVICE_STARTING(NAME)
#define SET_SERVICE_STARTED(NAME)
#define GET_SERVICE_STATUS(NAME)	SERVICE_STATUS_STARTED
*/
static void set_service_starting(uint8_t* name)
{
    uint8_t key[STR_LEN];
    memset(key, 0, STR_LEN);
    sprintf(key, "%s.%s", SERVICE_STATUS, name);

    SET_SERVICE_STARTING(key);
}

static void set_service_stoping(uint8_t* name)
{
    uint8_t key[STR_LEN];
    memset(key, 0, STR_LEN);
    sprintf(key, "%s.%s", SERVICE_STATUS, name);

    SET_SERVICE_STOPING(key);
}

static void set_service_started(uint8_t* name)
{
    uint8_t key[STR_LEN];
    memset(key, 0, STR_LEN);
    sprintf(key, "%s.%s", SERVICE_STATUS, name);

    SET_SERVICE_STARTED(key);
}

static void set_service_stoped(uint8_t* name)
{
    uint8_t key[STR_LEN];
    memset(key, 0, STR_LEN);
    sprintf(key, "%s.%s", SERVICE_STATUS, name);

    SET_SERVICE_STOPED(key);
}

static uint8_t is_service_started(uint8_t* name)
{
    uint8_t key[STR_LEN];
    memset(key, 0, STR_LEN);
    sprintf(key, "%s.%s", SERVICE_STATUS, name);

    if(GET_SERVICE_STATUS(key) == SERVICE_STATUS_STARTED)
        return 1;
    return 0;
}

static uint8_t is_service_stoped(uint8_t* name)
{
    uint8_t key[STR_LEN];
    memset(key, 0, STR_LEN);
    sprintf(key, "%s.%s", SERVICE_STATUS, name);

    if(GET_SERVICE_STATUS(key) == SERVICE_STATUS_STOPED)
        return 1;
    return 0;
}

static void wait_service_started(uint8_t* name)
{
    uint8_t key[STR_LEN];
    memset(key, 0, STR_LEN);
    sprintf(key, "%s.%s", SERVICE_STATUS, name);

    if(strcmp(name, "") == 0) {
        return ;
    }

    while(1) {
        if(GET_SERVICE_STATUS(key) == SERVICE_STATUS_STARTED)
		break;
	sleep(1);
    }

}

static void wait_service_stoped(uint8_t* name)
{
    uint8_t key[STR_LEN];
    memset(key, 0, STR_LEN);
    sprintf(key, "%s.%s", SERVICE_STATUS, name);

    while(1) {
        if(GET_SERVICE_STATUS(key) == SERVICE_STATUS_STOPED)
		break;
	sleep(1);
    }

}

static uint32_t get_service_status(uint8_t* name)
{
    uint8_t key[STR_LEN];
    memset(key, 0, STR_LEN);
    sprintf(key, "%s.%s", SERVICE_STATUS, name);
    return GET_SERVICE_STATUS(key);
}

static uint32_t get_progress_status(uint8_t* name)
{
    uint8_t key[STR_LEN];
    memset(key, 0, STR_LEN);
    sprintf(key, "%s.%s", PROGRESS_STATUS, name);
    return GET_PROGRESS_STATUS(key);
}

static void set_progress_status(uint8_t* name, uint32_t status)
{
    uint8_t key[STR_LEN];
    memset(key, 0, STR_LEN);
    sprintf(key, "%s.%s", PROGRESS_STATUS, name);

    SET_PROGRESS_STATUS(key, status);
}

//static struct ops_cfg_bdb_status_t* obj = NULL;

DEFINE_INSTANCE(cfg_status, bdb);
DEFINE_GET_INSTANCE(cfg_status, bdb)
{
    if(!obj) {
        obj = malloc(sizeof(struct ops_cfg_status_t));
	obj->get_service_status = get_service_status;
	obj->is_service_started = is_service_started;
	obj->is_service_stoped = is_service_stoped;

	obj->set_service_starting = set_service_starting;
	obj->set_service_started = set_service_started;
	obj->wait_service_started = wait_service_started;

	obj->set_service_stoping = set_service_stoping;
	obj->set_service_stoped = set_service_stoped;
	obj->wait_service_stoped = wait_service_stoped;

	obj->get_progress_status = get_progress_status;
	obj->set_progress_status = set_progress_status;
    }

    return obj;
}

DEFINE_DEL_INSTANCE(cfg_status, bdb)
{
    if(obj)
        free(obj);
}

