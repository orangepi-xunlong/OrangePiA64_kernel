#ifndef _ORANGEPI_DEBUG_H_
#define _ORANGEPI_DEBUG_H_

#define CLOSE_ALL_DEBUG_LOG       0x00000000
#define COMMON_DEBUG              0x00000001

#define _debug(fmt, ...) \
			printk(KERN_ERR fmt, ##__VA_ARGS__)  \

#endif
