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

#include "iopcops_cfg_bdb_status.h"

/*
 * Service Starting --> processing --> Service Started
 * is Service Started
 *
 * Service Stoping --> processing --> Service Stoped
 * is Service Stoped
 */

static void set_service_starting(uint8_t* name)
{
    GET_INSTANCE(cfg_status, bdb)->set_service_starting(name);
}

static void set_service_stoping(uint8_t* name)
{
    GET_INSTANCE(cfg_status, bdb)->set_service_stoping(name);
}

static void set_service_started(uint8_t* name)
{
    GET_INSTANCE(cfg_status, bdb)->set_service_started(name);
}

static void set_service_stoped(uint8_t* name)
{
    GET_INSTANCE(cfg_status, bdb)->set_service_stoped(name);
}

static uint8_t is_service_started(uint8_t* name)
{
    GET_INSTANCE(cfg_status, bdb)->is_service_started(name);
}

static uint8_t is_service_stoped(uint8_t* name)
{
    GET_INSTANCE(cfg_status, bdb)->is_service_stoped(name);
}

static void wait_service_started(uint8_t* name)
{
    GET_INSTANCE(cfg_status, bdb)->wait_service_started(name);
}

static void wait_service_stoped(uint8_t* name)
{
    GET_INSTANCE(cfg_status, bdb)->wait_service_stoped(name);
}

static uint32_t get_service_status(uint8_t* name)
{
    uint32_t result = 0;

    result = GET_INSTANCE(cfg_status, bdb)->get_service_status(name);

    return result;
}

static uint32_t get_progress_status(uint8_t* name)
{
    uint32_t result = 0;

    result = GET_INSTANCE(cfg_status, bdb)->get_progress_status(name);

    return result;
}

static void set_progress_status(uint8_t* name, uint32_t status)
{
    GET_INSTANCE(cfg_status, bdb)->set_progress_status(name, status);
}

//static struct ops_cfg_bdb_status_t* obj = NULL;

DEFINE_INSTANCE(cfg_status, ifc);
DEFINE_GET_INSTANCE(cfg_status, ifc)
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

DEFINE_DEL_INSTANCE(cfg_status, ifc)
{
    if(obj)
        free(obj);
}

