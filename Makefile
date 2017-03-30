
TARGET = libiopccommon.so

CFLAGS += -I$(SDKSTAGE)/usr/include/json-c
CFLAGS += -I$(SDKSTAGE)/usr/include/
CFLAGS += -I./include/
CFLAGS += 

LDFLAGS += -L$(SDKSTAGE)/usr/lib/ 
LDFLAGS += -lc -lpthread -ldl
LDFLAGS += -ljson-c
LDFLAGS += -ldb

SRC = 
SRC += ops_misc.c
SRC += ops_vmimg.c
SRC += ops_mq.c

SRC += ops_cfg/platform.c
SRC += ops_cfg/network.c
SRC += ops_cfg/mountfs.c
SRC += ops_cfg/vm.c
SRC += ops_cfg/status.c
SRC += ops_cfg/plugincmd.c

#SRC += ops_cfg_json/dao.c

SRC += ops_cfg_bdb/dao.c
SRC += ops_cfg_bdb/platform.c
SRC += ops_cfg_bdb/network.c
SRC += ops_cfg_bdb/mountfs.c
SRC += ops_cfg_bdb/vm.c
SRC += ops_cfg_bdb/status.c
SRC += ops_cfg_bdb/plugincmd.c

include Makefile.include.lib
