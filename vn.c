#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ioccom.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <mach/boolean.h>
#include <errno.h>

#define VNIOCATTACH _IOWR('F', 0, struct vn_ioctl)  /* attach file */
#define VNIOCDETACH _IOWR('F', 1, struct vn_ioctl)  /* detach disk */
typedef enum {
    vncontrol_readwrite_io_e = 0
} vncontrol_t;

struct vn_ioctl {
    char *      vn_file;    /* pathname of file to mount */
    int         vn_size;    /* (returned) size of disk */
    vncontrol_t vn_control;
};

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "Usage: ./vn /dev/vnX [image, or leave blank to detach]\n");
        return 1;
    }
    struct vn_ioctl vn;
    memset(&vn, 0, sizeof(vn));
    int fd = open(argv[1], O_RDONLY, 0);
    if(!fd) {
        fprintf(stderr, "Could not open %s: %s", argv[1], strerror(errno));
        return 1;
    }
    ioctl(fd, VNIOCDETACH, &vn);
    if(argc <= 2) return 0;
    vn.vn_file = argv[2];
    vn.vn_control = vncontrol_readwrite_io_e;
    int ret = ioctl(fd, VNIOCATTACH, &vn);
    if(ret) {
        fprintf(stderr, "VNIOCATTACH failed: %s", strerror(errno));
        return 1;
    }
    close(fd);
    return 0;
}
