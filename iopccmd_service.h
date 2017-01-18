#ifndef IOPCCMD_SERVICE_H
#define IOPCCMD_SERVICE_H

#define SERVICE_ACTION_STATUS   (0x00)
#define SERVICE_ACTION_START    (0x01)
#define SERVICE_ACTION_STOP     (0x02)
#define SERVICE_ACTION_RESTART  (0x03)

#define SERVICE_ACTION_STATUS_SPECIFIC	(0x80 | SERVICE_ACTION_STATUS)
#define SERVICE_ACTION_START_SPECIFIC	(0x80 | SERVICE_ACTION_START)
#define SERVICE_ACTION_STOP_SPECIFIC	(0x80 | SERVICE_ACTION_STOP)
#define SERVICE_ACTION_RESTART_SPECIFIC (0x80 | SERVICE_ACTION_RESTART)

struct arg_t {
    uint8_t index;
} __PACKED__;

struct req_service_t {
    uint8_t action;
}__PACKED__;
struct res_service_t {
    uint8_t status;
    uint8_t action;
    uint32_t service_status;
}__PACKED__;

struct req_background_t {
    uint8_t libname_len;
    uint8_t funcname_len;
    uint8_t str[MAX_STR_VAL];
}__PACKED__;

#endif
