#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <db.h>

#include "iopcdefine.h"
#include "iopcops_cfg.h"

static void init()
{
    GET_INSTANCE(cfg_bdb, ifc)->init();
}

static void show_all(uint8_t* cfg_file)
{
    GET_INSTANCE(cfg_bdb, ifc)->show_all(cfg_file)
}

DEFINE_INSTANCE(cfg, ifc);
DEFINE_GET_INSTANCE(cfg, ifc)
{
    if(!obj) {
        obj = malloc(sizeof(struct ops_cfg_t));
	obj->init = init;
        obj->show_all = show_all;
    }

    return obj;
}

DEFINE_DEL_INSTANCE(cfg, ifc)
{
    if(obj)
        free(obj);
}

