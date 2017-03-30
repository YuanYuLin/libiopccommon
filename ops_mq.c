#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include "iopcdefine.h"
#include "iopcops_mq.h"

static mqd_t create(uint8_t* id)
{
    char path[30];
    mqd_t mqd;

    memset(path, 0, sizeof(path));
    sprintf(path, "/MQ%s", id);

//    printf("MQ creating : %s\n", path);
    mqd = mq_open(path, O_RDWR | O_CREAT | O_EXCL, S_IRWXU | S_IRWXG | S_IRWXO, NULL);

    if((mqd < 0) && (errno == EEXIST)) {
        mqd = mq_open(path, O_RDWR, NULL);
    }

    if(mqd < 0) {
        printf("MQ created ERROR :(%d) %s\n", errno, path);
	return -1;
    }
    return mqd;
}

static void delete(uint8_t* id)
{
    char path[30];
    memset(path, 0, sizeof(path));
    sprintf(path, "/MQ%s", id);
    mq_unlink(path);
}

static int get(mqd_t mqd, struct msg_t* msg)
{
    struct mq_attr attr;
    ssize_t msg_size = 0;
    char *ptr = (char*)msg;

    mq_getattr(mqd, &attr);
    memset(msg, 0, sizeof(struct msg_t));

    msg_size = mq_receive(mqd, ptr, attr.mq_msgsize, NULL);
    if(msg_size < 0) {
        printf("MQ_RCV:%d:%d\n", errno, attr.mq_msgsize);
	return 0;
    }

    return msg_size;
}

static int set(mqd_t mqd, struct msg_t* msg)
{
    int size = sizeof(struct msg_hdr_t) + msg->hdr.data_size;
    int ret = 0;

    ret = mq_send(mqd, (const char*)msg, size, 0);
    return ret;
}

static void destroy(uint8_t* id)
{
    delete(id);
}

static int get_from(uint8_t* id, struct msg_t* msg)
{
    int ret = 0;
    mqd_t mqd = create(id);
    ret = get(mqd, msg);
    mq_close(mqd);
    //destroy(mqd);
    return ret;
}

static int set_to(uint8_t* id, struct msg_t* msg)
{
    int ret = 0;
    mqd_t mqd = create(id);
    ret = set(mqd, msg);
    mq_close(mqd);
    //destroy(mqd);
    return ret;
}
#if 0
struct ops_mq_t ops_mq = {
    .create = create,
    .destroy = destroy,
    .get = get,
    .set = set,
    .get_from = get_from,
    .set_to = set_to,
};
#else
//static struct ops_mq_t* obj = NULL;
#endif

DEFINE_INSTANCE(mq, obj);
DEFINE_GET_INSTANCE(mq, obj)
{
//    struct ops_mq_t* obj = NULL;
    if(!obj) {
        obj = malloc(sizeof(struct ops_mq_t));
	obj->create = create;
	obj->destroy = destroy;
	obj->get = get;
	obj->set = set;
	obj->get_from = get_from;
	obj->set_to = set_to;
    }

    return obj;
}

DEFINE_DEL_INSTANCE(mq, obj)
{
    if(obj)
        free(obj);
}

