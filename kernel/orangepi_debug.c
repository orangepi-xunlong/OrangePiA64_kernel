#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/orangepi_debug.h>


void _debug(void)
{
	printk("SD\n");
}
EXPORT_SYMBOL(_debug);
