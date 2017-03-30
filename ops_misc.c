#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/loop.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <net/if.h>
#include <dlfcn.h>
#include <pthread.h>
#include <mntent.h> 

#include "include/iopcdefine.h"
#include "iopcops_misc.h"
#include "iopcops_mq.h"
#include "iopccmd_service.h"

static int is_exist(uint8_t* path)
{
    struct stat st;
    if(stat(path, &st) != 0) {
        printf("[%s] is not exist\n", path);
        return -1;
    }
    return 0;
}

static void create_dir_recursive(const char *dir, mode_t mode)
{
    char tmp[STR_LEN];
    char *p = NULL;
    size_t len;

    sprintf(tmp, "%s",dir);
    len = strlen(tmp);
    if(tmp[len - 1] == '/')
        tmp[len - 1] = 0;
    for(p = tmp + 1; *p; p++)
        if(*p == '/') {
            *p = 0;
            mkdir(tmp, mode);
            *p = '/';
        }
    mkdir(tmp, mode);
}

static int bind_loopdev(uint8_t * file, uint8_t * loop_dev, uint64_t offset)
{
    int ffd = -1;
    int dfd = -1;
    struct loop_info64 info;

    ffd = open(file, O_RDONLY);
    if(ffd < 0) {
        printf("Failed to open file (%s)\n", file);
	return -1;
    }

    dfd = open(loop_dev, O_RDONLY);
    if(dfd < 0) {
        printf("Failed to open dev (%s)\n", loop_dev);
	close(ffd);
	return -1;
    }

    if(ioctl(dfd, LOOP_SET_FD, ffd) < 0) {
        printf("Failed to set fd(%s->%s)\n", file, loop_dev);
	close(ffd);
	close(dfd);
	return -1;
    }

    close(ffd);
    ffd = -1;

    memset(&info, 0, sizeof(struct loop_info64));
    info.lo_offset = offset;

    if(ioctl(dfd, LOOP_SET_STATUS64, &info)) {
        printf("Failed to set info(%s)\n", loop_dev);
	close(dfd);
	return -1;
    }

    close(dfd);
    dfd = -1;

    printf("BIND  %s to %s success\n", file, loop_dev);

    return 0;
}

extern int init_module(void *module_image, unsigned long len, const char *param_values);

static int install_module(char* part)
{
    int mod_fd;
    struct stat st;
    size_t module_size;
    void *module;
    int mmaped = 0;
    char mod_name[256] = { 0 };

    memset((void*)&mod_name, 0, sizeof(mod_name));
    sprintf(mod_name, MODULE_PATH, part);

    if(stat(mod_name, &st) != 0) {
        printf("module is not exist[%s]\n", mod_name);
	return -1;
    }
    module_size = st.st_size;

    mod_fd = open(mod_name, O_RDONLY);
    if(mod_fd < 0) {
        printf("open module failed[%s]\n", mod_name);
	return -1;
    }

    module = mmap(0, module_size, PROT_READ, MAP_PRIVATE, mod_fd, 0);
    close(mod_fd);

    if(module) {
        mmaped = 1;
    }

    init_module(module, module_size, "");

    if(mmaped)
        munmap(module, module_size);

    return 0;
}

static int mountfs(uint8_t *src, uint8_t *dst, uint8_t* type, uint32_t flags, uint8_t* opts)
{
    printf("Mount %s to %s as %s [%x, %s]\n", src, dst, type, flags, opts);
    mount(src, dst, type, flags, opts);
    return 0;
}

static int umountfs(uint8_t *dst, uint32_t flags)
{
    if(flags == 0) {
        umount(dst);
    } else {
        umount2(dst, flags);
    }

    return 0;
}

static int is_mountfs_by_src_dst_type(uint8_t *src, uint8_t *dst, uint8_t* type)
{
    struct mntent *mnt;
    FILE *fd = NULL;
    fd = setmntent("/proc/mounts","r");
    if(!fd)
        return -1;
    while ((mnt = getmntent(fd))) {
        //printf("fsname: %s, dir: %s, type: %s, opts:%s\n", mnt->mnt_fsname, mnt->mnt_dir, mnt->mnt_type, mnt->mnt_opts);
	if((strcmp(src, mnt->mnt_fsname) == 0) &&
        (strcmp(dst, mnt->mnt_dir) == 0) &&
        (strcmp(type, mnt->mnt_type) == 0)) {
            return 1;
        }
    }
    endmntent(fd);
    return 0;
}

static int create_system_by_node(struct root_t *node)
{
        switch(node->type) {
        case ROOT_TYPE_CREATE_DIR:
            //mkdir(node->opt1, (mode_t)node->opt2);
	    create_dir_recursive((char*)node->opt1.ptr, (mode_t)node->opt2.mode);
            //mkdir(node->opt1, *((mode_t*)node->opt2));
	break;
	case ROOT_TYPE_CREATE_FILE:
	    creat(node->opt1.ptr, (mode_t)node->opt2.mode);
	    printf("CREATE_FILE MODE %x\n", node->opt2.ptr);
	break;
	case ROOT_TYPE_MOUNT_PROC:
	    mount("proc", node->opt1.ptr, "proc", node->flags, node->opt2.ptr);
	break;
	case ROOT_TYPE_MOUNT_TMPFS:
	    mount("tmpfs", node->opt1.ptr, "tmpfs", node->flags, node->opt2.ptr);
	break;
	case ROOT_TYPE_MOUNT_SQUASHFS:
	    mount(node->opt1.ptr, node->opt2.ptr, "squashfs", node->flags, NULL);
	break;
	case ROOT_TYPE_CREATE_SYMBOL:
	    unlink(node->opt2.ptr);
	    symlink(node->opt1.ptr, node->opt2.ptr);
	break;
        case ROOT_TYPE_MOUNT_DEVTMPFS:
	    mount("udev", node->opt1.ptr, "devtmpfs", node->flags, node->opt2.ptr);
	break;
	case ROOT_TYPE_MOUNT_DEVPTS:
	    mount("lxcdevpts", node->opt1.ptr, "devpts", node->flags, node->opt2.ptr);
	break;
	case ROOT_TYPE_MOUNT_SYSFS:
	    mount("sysfs", node->opt1.ptr, "sysfs", node->flags, node->opt2.ptr);
	break;
	case ROOT_TYPE_MOUNT_MQUEUE:
	    mount("mqueue", node->opt1.ptr, "mqueue", node->flags, node->opt2.ptr);
	break;
	case ROOT_TYPE_MOUNT_CGROUP:
	    mount("cgroup", node->opt1.ptr, "cgroup", node->flags, node->opt2.ptr);
	break;
	case ROOT_TYPE_INSERT_MODULE:
	    install_module(node->opt1.ptr);
	break;
	case ROOT_TYPE_BIND_LOOP:
	    bind_loopdev(node->opt1.ptr, node->opt2.ptr, node->flags);
	break;
	}
	return 0;
}

static int create_system_by_list(int list_size, struct root_t* list)
{
    struct root_t *node = NULL;
    int i = 0;

    for(i=0;i<list_size;i++) {
        node = &list[i];
        create_system_by_node(node);
    }
    return 0;
}

static int plugin_new_cmd(uint8_t* full_path, callback_cmd_fn_t callback, uint8_t group, uint8_t cmd, uint8_t* cmd_name)
{
    void *dl_handle;
    struct cmd_desc_t* cmd_ptr = NULL;

    printf("Pluging [(%s)%s - %d - %d] ", full_path, cmd_name, group, cmd);

    if(is_exist(full_path) < 0) {
        printf("[%s] is not exist!\n", full_path);
	return -1;
    }

    dl_handle = dlopen((const char*)full_path, RTLD_LAZY);
    if(!dl_handle){
        printf("dlopen [%s] error[%s]\n", full_path, dlerror());
	return -1;
    }
    struct cmd_desc_t* cmd_desc_list = (struct cmd_desc_t*)dlsym(dl_handle, FUNC_CMD_DESC_TABLE);
    //uint32_t cmd_descs_count = (sizeof(cmd_desc_list)/sizeof(cmd_desc_list[0]));//(uint32_t)dlsym(dl_handle, FUNC_CMD_DeSC_TABLE_COUNT);

    if(cmd_desc_list == NULL) {
        printf("Load dlsym[%s-%s] error...\n", full_path, FUNC_CMD_DESC_TABLE);
	dlclose(dl_handle);
	return -1;
    }

    cmd_ptr = cmd_desc_list;
    //printf("cmd count %ld, %ld, %x\n", sizeof(struct cmd_desc_t), sizeof(cmd_desc_list), cmd_ptr);
    for(;;++cmd_ptr) {
        //printf("%x\n", cmd_ptr);
	if(cmd_ptr->fn_str_name == NULL) {
            printf("name:%s\n", cmd_ptr->fn_str_name);
            return -1;
	}
        //printf("fn_name:%s\n", cmd_ptr->fn_str_name);

        if(strcmp(cmd_ptr->fn_str_name, "") == 0) {
	       /*	&& 
			(strcmp(cmd_ptr->fn_str_filter, "") == 0) &&
			(strcmp(cmd_ptr->fn_str_handler, "") == 0)) {
			*/
            break;
	}

	if(strcmp(cmd_ptr->fn_str_name, cmd_name) == 0) {
            //cmd_filter_fn_t cmd_filter = (cmd_filter_fn_t)dlsym(dl_handle, cmd_ptr->fn_str_filter);
            //cmd_handler_fn_t cmd_handler = (cmd_handler_fn_t)dlsym(dl_handle, cmd_ptr->fn_str_handler);
	    callback((void*)dl_handle, group, cmd, cmd_ptr->cmd_filter, cmd_ptr->cmd_handler);
	    printf("registered\n");
	    return 0;
	}
    }
    printf("register failed\n");
    return 0;
}

static int plugin_new_task(uint8_t* full_path, callback_task_fn_t callback)
{
    void *dl_handle;
    struct task_desc_t* task_ptr = NULL;
    pthread_t task_id;

    if(is_exist(full_path) < 0) {
        printf("[%s] is not exist!\n");
    }

    dl_handle = dlopen((const char*)full_path, RTLD_LAZY);
    if(!dl_handle){
        printf("dlopen [%s] error[%s]\n", full_path, dlerror());
	return -1;
    }
    struct task_desc_t* task_descs = (struct task_desc_t*)dlsym(dl_handle, FUNC_TASK_DESC_TABLE);

    task_ptr = task_descs;
    for(;;++task_ptr) {
        if((strcmp(task_ptr->fn_str_name, "") == 0) &&
		    (strcmp(task_ptr->fn_str_help, "") == 0) &&
		    (strcmp(task_ptr->fn_str_handler, "") == 0)) {
            break;
        }

        get_name_fn_t get_name = (get_name_fn_t)dlsym(dl_handle, task_ptr->fn_str_name);
        get_help_fn_t get_help = (get_help_fn_t)dlsym(dl_handle, task_ptr->fn_str_help);
        task_start_fn_t task_start = (task_start_fn_t)dlsym(dl_handle, task_ptr->fn_str_handler);
        pthread_create(&task_id, NULL, task_start, NULL);
	callback((void*)dl_handle, (void*)task_id, get_name, get_help);
    }
    return 0;
}

static int execute_cmd(char* cmd, char* log_file)
{
    system(cmd);
    return 0;
}

static int copy_file(uint8_t* src, uint8_t *dst)
{
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];
    inputFd = open(src, O_RDONLY);
    if (inputFd == -1){
        printf("error:opening src file %s\n", src);
	return -1;
    }
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;/* rw-rw-rw- */
    outputFd = open(dst, openFlags, filePerms);
    if (outputFd == -1){
        printf("error:opening dst file %s\n", dst);
	return -1;
    }

    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
        if (write(outputFd, buf, numRead) != numRead){
            printf("error: couldn't write whole buffer");
	}

    if (numRead == -1){
        printf("error: read\n");
        return -1;
    }

    if(close(inputFd) == -1) {
        printf("error: close input\n");
    }
    if(close(outputFd) == -1) {
        printf("error: close output\n");
    }
    return 0;
}

static int get_ctl_fd(void)
{
    int fd;

    fd = socket(PF_INET, SOCK_DGRAM, 0);
    if (fd >= 0)
        return fd;
    fd = socket(PF_PACKET, SOCK_DGRAM, 0);
    if (fd >= 0)
        return fd;
    fd = socket(PF_INET6, SOCK_DGRAM, 0);
    return fd;
}

static int is_netdev_up(uint8_t *dev)
{
    int fd = -1;
    struct ifreq ifr;
    printf("run is_netdev_up(%d)\n", dev);
    fd = get_ctl_fd();
    memset((void*)&ifr, 0, sizeof(ifr));
    memcpy(ifr.ifr_name, dev, strlen(dev));

    printf("FD is %d\n", fd);
    ioctl(fd, SIOCGIFFLAGS, &ifr);
    close(fd);

    printf("Flags are %x\n", ifr.ifr_flags);

    if(ifr.ifr_flags & IFF_UP) {
        printf("is up\n");
        return 0;
    }

    printf("is not up\n");
    return -1;
}

#define TASK_TIMER	"tasktimer"
static void post_to_background(uint8_t* libname, uint8_t* funcname)
{
    struct msg_t req;
    struct req_background_t* req_background = NULL;

    req_background = (struct req_background_t*)&req.data;

    memset((uint8_t*)&req_background->str[0], 0, MAX_STR_VAL);
    req_background->libname_len = strlen(libname);
    req_background->funcname_len = strlen(funcname);
    sprintf(req_background->str, "%s%s", libname, funcname);

    strcpy(req.hdr.src, "");
    strcpy(req.hdr.dst, TASK_TIMER);
    req.hdr.fn = 0xAA;
    req.hdr.cmd = 0x55;
    req.hdr.data_size = sizeof(req_background->libname_len) + sizeof(req_background->funcname_len) + req_background->libname_len + req_background->funcname_len;

    GET_INSTANCE(mq, obj)->set_to(req.hdr.dst, &req);
}

static void create_task(task_start_fn_t task_start)
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, task_start, NULL);
}

static void create_task_with_arg(task_start_fn_t task_start, void* arg, uint32_t arg_size)
{
    pthread_t thread_id;
    void* ptr = malloc(arg_size);
    memcpy((void*)ptr, (void*)arg, (size_t)arg_size);
    pthread_create(&thread_id, NULL, task_start, ptr);
}

static uint32_t get_text(uint8_t* file, uint8_t* buffer, uint32_t offset, uint32_t max)
{
    uint32_t len = 0;
    FILE *fd;

    fd = fopen(file, "r");
    if(fd == NULL) {
        return 0;
    }
    fseek(fd, offset, SEEK_SET);
    len = fread(buffer, 1, max, fd);
//    printf("fRead %d\n", len);
    fclose(fd);

    return len;
}

/*
static struct ops_misc_t ops_misc = {
    .name = "misc",
    .create_dir_recursive = create_dir_recursive,
    .create_system_by_list = create_system_by_list,
    .is_exist = is_exist,
    .bind_loopdev = bind_loopdev,
    .install_module = install_module,
    .plugin_new_task = plugin_new_task,
    .execute_cmd = execute_cmd,
    .copy_file = copy_file,
};
*/

//static struct ops_misc_t* obj = NULL;

//struct ops_misc_t* create_instance_ops_misc()
DEFINE_INSTANCE(misc, obj);
DEFINE_GET_INSTANCE(misc, obj)
{
//    struct ops_misc_t* obj = NULL;
    if(!obj) {
        obj = malloc(sizeof(struct ops_misc_t));
        obj->create_dir_recursive = create_dir_recursive;
        obj->create_system_by_list = create_system_by_list;
        obj->is_exist = is_exist;
        obj->bind_loopdev = bind_loopdev;
        obj->install_module = install_module;
        obj->plugin_new_task = plugin_new_task;
	obj->plugin_new_cmd = plugin_new_cmd;
        obj->execute_cmd = execute_cmd;
        obj->copy_file = copy_file;
	obj->is_netdev_up = is_netdev_up;
	obj->post_to_background = post_to_background;
	obj->create_task = create_task;
	obj->create_task_with_arg = create_task_with_arg;
	obj->get_text = get_text;
	obj->mountfs = mountfs;
	obj->umountfs = umountfs;
	obj->is_mountfs_by_src_dst_type = is_mountfs_by_src_dst_type;
    }
    return obj;
}

//void destroy_instance_ops_misc(struct ops_misc_t* obj)
DEFINE_DEL_INSTANCE(misc, obj)
{
    if(obj)
        free(obj);
}

