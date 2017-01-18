
TARGET = libiopccommon.so

CFLAGS += -I$(SDKSTAGE)/usr/include/json-c
CFLAGS += -I$(SDKSTAGE)/usr/include/
CFLAGS += 

LDFLAGS += -L$(SDKSTAGE)/usr/lib/ 
LDFLAGS += -lc -lpthread -ldl
LDFLAGS += -ljson-c
LDFLAGS += -ldb

SRC = 
SRC += ops_misc.c
SRC += ops_vmimg.c
SRC += ops_mq.c
SRC += ops_cfg_json.c
SRC += ops_cfg_bdb.c
SRC += ops_cfg_bdb_platform.c
SRC += ops_cfg_bdb_network.c
SRC += ops_cfg_bdb_mountfs.c
SRC += ops_cfg_bdb_vm.c
SRC += ops_cfg_bdb_status.c
SRC += ops_cfg_bdb_plugincmd.c

include Makefile.include.lib
