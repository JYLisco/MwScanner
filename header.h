#include <linux/ioctl.h>

#define DEVICE_NAME "mw_scanner"
#define DEVICE_PATH "/dev/mw_scanner"
#define MAGIC_NO '4'

#define READ_PROC _IOR(MAGIC_NO, 0, char*)
#define READ_MEM _IOR(MAGIC_NO, 1, char*)
#define READ_TBL _IO(MAGIC_NO, 2)