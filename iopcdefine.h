#ifndef IOPCDEFINE_H
#define IOPCDEFINE_H

#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <pthread.h>

#define PS_TYPE_MASK			0xFF00
#define PS_STAGE_MASK			0x00F0
#define PS_ERRORNO_MASK			0x000F

#define PROGRESS_TYPE_UNKNOW		0x0000
#define PROGRESS_TYPE_STAGE		0x0100

#define PS_STAGE_UNKNOW			0x0000
#define PS_STAGE_INPROGRESS		0x0010
#define PS_STAGE_SUCCESSED		0x0040
#define PS_STAGE_FAILED			0x0080

#define CMD_STATUS			0x00
#define CMD_ADD				0x01
#define CMD_COUNT			0x02
#define CMD_GET				0x03
#define CMD_SET				0x04

#define CLA_SERVICE			0x01
#define CLA_BASE			0x02
#define CLA_ACTION			0x03
#define CLA_DB				0x04

#define INIT_MNTBASE			0x01
#define INIT_RAIDDEV			0x02
#define INIT_NETDEV			0x03
#define INIT_NETNTP			0x04
#define INIT_NETSSH			0x05
#define INIT_VM				0x06
#define INIT_NETHTTP			0x07

#define OP_MKBTRFS_STATUS		(CMD_STATUS)
#define OP_MKBTRFS			0x01

#define FN_RAID				0x08
#define RAIDDEV_ADD			(FN_RAID | CMD_ADD)
#define RAIDDEV_COUNT			(FN_RAID | CMD_COUNT)
#define RAIDDEV_GET			(FN_RAID | CMD_GET)
#define RAIDDEV_SET			(FN_RAID | CMD_SET)

#define FN_MNTBASE			0x00
#define MNTBASE_ADD			(FN_MNTBASE | CMD_ADD)
#define MNTBASE_COUNT			(FN_MNTBASE | CMD_COUNT)
#define MNTBASE_GET			(FN_MNTBASE | CMD_GET)
#define MNTBASE_SET			(FN_MNTBASE | CMD_SET)

#define FN_VM				0x10
#define VM_ADD				(FN_VM | CMD_ADD)
#define VM_COUNT			(FN_VM | CMD_COUNT)
#define VM_GET				(FN_VM | CMD_GET)
#define VM_SET				(FN_VM | CMD_SET)

#define GET_BOOL_FLASH			0x00
#define SET_BOOL_FLASH			0x01
#define GET_UINT32_FLASH		0x02
#define SET_UINT32_FLASH		0x03
#define GET_STRING_FLASH		0x04
#define SET_STRING_FLASH		0x05
#define SAVE2PERSIST			0x07

#define GET_BOOL_RAM			0x08
#define SET_BOOL_RAM			0x09
#define GET_UINT32_RAM			0x0A
#define SET_UINT32_RAM			0x0B
#define GET_STRING_RAM			0x0C
#define SET_STRING_RAM			0x0D
#define RESTORE2DEFAULT			0x0F

#define STR_LEN				(255)
#define VM_NAME_LEN			(30)
#define VM_NETTYPE_LEN			(10)
#define VM_NETHWLINK_LEN		(10)
#define VM_NETHWADDR_LEN		(18)

#define MNTBASE_NAME_LEN		(30)
#define MNTBASE_TYPE_LEN		(10)

#define MIN_RAID_COUNT			(2)
#define MAX_RAID_COUNT			(32)
#define RAIDDEV_NAME_LEN		(20)
#define RAIDDEV_TYPE_LEN		(15)
#define RAIDDEV_PATH_LEN		(25)
#define IOPC_DIR_RAID			"/raid"

#define BUF_SIZE			(1024)
#define MAX_TASK_SIZE			(10)
#define MAX_CMD_GROUP_SIZE		(0x5) // (0x10)
#define MAX_CMD_SIZE			(0x0F)// (0xFF)
#define MAX_MSG_DATA_SIZE		(1024*2)
#define MAX_STR_VAL			(1000)

#define DEFAULT_MODE			(0x1B6)

#define DB_TYPE_STRING			"STRING"
#define DB_TYPE_UINT32			"UINT32"
#define DB_TYPE_BOOLEAN			"_BOOL_"
#define DB_MEDIA_UNKNOW			0x00
#define DB_MEDIA_FLASH			0x01
#define DB_MEDIA_RAM			0x02

#define IOPC_VMBASE_PATH		"/persist/vmbase"
#define IOPC_VMLIST_PATH		"/persist/vmlist"
#define IOPC_PERSIST_PATH		"/persist"
#define IOPC_PERSIST_CFGS_PATH		"/persist/cfgsdb.flash"
//#define IOPC_CFG_PATH			IOPC_PERSIST_PATH"/iopc"
//#define IOPC_VMS_PATH			IOPC_PERSIST_PATH"/vms"
#define IOPC_DEFCFG_PATH		"/etc/iopc"
#define MODULE_PATH			"/lib/modules/modules_kernel%s"
#define FUNC_TASK_DESC_TABLE		"task_descs"
#define FUNC_CMD_DESC_TABLE		"cmd_descs"
#define FUNC_CMD_DeSC_TABLE_COUNT	"cmd_descs_count"
#define IOPC_LIBS_PATH(SO_OBJ)		"/usr/local/lib/"#SO_OBJ
#define USR_LIBS_PATH			"/usr/local/lib"

#define TASK_IOPCLAUNCHER		"iopclaunch"

#define INIT_NODE(val1,val2,val3,val4)	{((uint8_t)val1),((void*)val2),((void*)val3),((uint32_t)val4)}

#define DEFINE_INSTANCE(NAME)		static struct NAME##_t* obj = NULL;
#define DEFINE_GET_INSTANCE(NAME)	struct NAME##_t* create_instance_##NAME(void)
#define DEFINE_DEL_INSTANCE(NAME)	void destroy_instance_##NAME(struct NAME##_t* obj)

#define GET_INSTANCE(NAME)		((struct NAME##_t*)create_instance_##NAME())
#define DEL_INSTANCE(NAME)		destroy_instance_##NAME(NAME)

#define ROOT_TYPE_UNKNOW                (0)
#define ROOT_TYPE_CREATE_DIR            (1)
#define ROOT_TYPE_CREATE_FILE           (2)
#define ROOT_TYPE_CREATE_SYMBOL         (3)
#define ROOT_TYPE_MOUNT_PROC            (4)
#define ROOT_TYPE_MOUNT_TMPFS           (5)
#define ROOT_TYPE_MOUNT_DEVTMPFS        (6)
#define ROOT_TYPE_MOUNT_SYSFS           (7)
#define ROOT_TYPE_MOUNT_MQUEUE          (8)
#define ROOT_TYPE_MOUNT_CGROUP          (9)
#define ROOT_TYPE_MOUNT_DEVPTS          (10)
#define ROOT_TYPE_MOUNT_SQUASHFS        (11)
#define ROOT_TYPE_INSERT_MODULE		(12)
#define ROOT_TYPE_BIND_LOOP		(13)

#define NETWORK_UNKNOW			(0)
#define NETWORK_GENERIC			(1)
#define NETWORK_BRIDGE			(2)
#define NETWORK_VLAN			(3)

#define __PACKED__			__attribute__((packed))

typedef uint8_t* (*get_help_fn_t)(void);
typedef uint8_t* (*get_name_fn_t)(void);
typedef uint32_t (*cmd_filter_fn_t)(uint8_t*, uint8_t*);
typedef uint32_t (*cmd_handler_fn_t)(uint8_t*, uint8_t*);
typedef void (*callback_task_fn_t)(void*, void*, get_name_fn_t, get_help_fn_t);
typedef void (*callback_cmd_fn_t)(void*, uint8_t, uint8_t, cmd_filter_fn_t, cmd_handler_fn_t);
typedef void* (*task_start_fn_t)(void*);

struct root_t {
    uint8_t type;
    void *opt1;
    void *opt2;
    uint32_t flags;
};

struct task_desc_t {
    uint8_t fn_str_name[20];
    uint8_t fn_str_help[20];
    uint8_t fn_str_handler[20];
};

struct task_t {
    uint8_t isused;
    void* dl_handle;
    void* task_id;
    get_name_fn_t get_name;
    get_help_fn_t get_help;
};

struct cmd_desc_t {
    uint8_t fn_str_name[20];
    cmd_filter_fn_t cmd_filter;
    cmd_handler_fn_t cmd_handler;
    //uint8_t fn_str_filter[20];
    //uint8_t fn_str_handler[20];
};

struct cmd_t {
//    uint8_t isused;
//    uint8_t event_id;
    void* dl_handle;
    uint8_t async_thread;
    pthread_t thread_id;
//    uint8_t cmd_group;
//    uint8_t cmd_id;
//    get_name_fn_t get_name;
//    get_help_fn_t get_help;
    cmd_filter_fn_t cmd_filter;
    cmd_handler_fn_t cmd_handler;
};

struct msg_hdr_t {
    uint32_t magic;
    uint8_t src[20];
    uint8_t dst[20];
    uint16_t data_size;
    uint8_t fn;
    uint8_t cmd;
    uint16_t crc16;
}__PACKED__;

struct msg_t {
    struct msg_hdr_t hdr;
    uint8_t data[MAX_MSG_DATA_SIZE];
}__PACKED__;

struct vmimg_t {
    uint32_t tag;
    uint32_t version;
    uint32_t crc32;
    uint32_t bin_size;
    uint32_t bin_offset;
}__PACKED__;

#endif

