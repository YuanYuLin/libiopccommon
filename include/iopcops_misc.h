#ifndef IOPCOPS_MISC_H
#define IOPCOPS_MISC_H

struct ops_misc_t {
    void (*create_dir_recursive)(const char *dir, mode_t mode);
    int (*copy_file)(uint8_t* src, uint8_t *dst);
    int (*is_exist)(uint8_t* path);
    int (*install_module)(char* part);
    int (*bind_loopdev)(uint8_t * file, uint8_t * loop_dev, uint64_t offset);
    int (*execute_cmd)(char* cmd, char* log_file);
    int (*create_system_by_list)(int list_size, struct root_t* list);
    int (*plugin_new_task)(uint8_t* full_path, callback_task_fn_t callback);
    int (*plugin_new_cmd)(uint8_t* full_path, callback_cmd_fn_t, uint8_t, uint8_t, uint8_t*);
    int (*is_netdev_up)(uint8_t *dev);
    void (*post_to_background)(uint8_t* libname, uint8_t* funcname);
    void (*create_task)(task_start_fn_t task_start);
    void (*create_task_with_arg)(task_start_fn_t task_start, void* arg, uint32_t arg_size);
    uint32_t (*get_text)(uint8_t* file, uint8_t* buffer, uint32_t offset, uint32_t max);
    int (*mountfs)(uint8_t *src, uint8_t *dst, uint8_t* type, uint32_t flags, uint8_t* opts);
    int (*umountfs)(uint8_t *dst, uint32_t flags);
    int (*is_mountfs_by_src_dst_type)(uint8_t *src, uint8_t *dst, uint8_t* type);
};

DEFINE_GET_INSTANCE(misc, obj);
DEFINE_DEL_INSTANCE(misc, obj);

#define GET_INSTANCE_MISC_OBJ() GET_INSTANCE(misc, obj)

#endif
