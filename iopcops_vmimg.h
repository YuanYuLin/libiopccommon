#ifndef IOPCOPS_VMIMG_H
#define IOPCOPS_VMIMG_H

#include <stdint.h>

struct ops_vmimg_t {
    uint8_t (*verify_img)(uint8_t* squashfs_file);
    uint8_t (*bind2loop)(uint32_t index, uint8_t* squashfs_file);
};

DEFINE_GET_INSTANCE(ops_vmimg);
DEFINE_DEL_INSTANCE(ops_vmimg);

#endif
