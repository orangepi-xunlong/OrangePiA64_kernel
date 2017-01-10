#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <linux/sys_config.h>

#include <linux/regulator/consumer.h>

#define DEV_NAME "orangepi_module"

/*
 * Open USB1 
 */
void open_USB1(void)
{
	struct device_node *node;
	unsigned int gpio;

	node = of_find_node_by_type(NULL, "usbc1");
	if (!node) {
		printk("Can't get device node\n");
		goto out;
	}

	gpio = of_get_named_gpio(node, "usb_drv_vbus_gpio", 0);
	if (gpio_is_valid(gpio)) {
		printk("GPIO %d valid\n", gpio);
		gpio_request(gpio, NULL);
		gpio_direction_output(gpio, 1);
		__gpio_set_value(gpio, 1);
	} else {
		printk("Request GPIO %d\n", gpio);
		__gpio_set_value(gpio, 1);
	}
	printk("USBC1 Current voltage is %d\n", __gpio_get_value(gpio));

out:
	;
}

/*
 * Open USB0 
 */
void open_USB0(void)
{
	struct device_node *node;
	unsigned int gpio;

	node = of_find_node_by_type(NULL, "usbc0");
	if (!node) {
		printk("Can't get device node\n");
		goto out;
	}

	gpio = of_get_named_gpio(node, "usb_drv_vbus_gpio", 0);
	if (gpio_is_valid(gpio)) {
		printk("GPIO %d valid\n", gpio);
		gpio_request(gpio, NULL);
		gpio_direction_output(gpio, 1);
		__gpio_set_value(gpio, 1);
	} else {
		printk("Request GPIO %d\n", gpio);
		__gpio_set_value(gpio, 1);
	}
	printk("USBC0 Current voltage is %d\n", __gpio_get_value(gpio));

out:
	;
}

static int buddy_open(struct inode *inode,struct file *filp)
{
	printk(KERN_INFO "Open device\n");
	return 0;
}
/*
 * write operation
 */
static ssize_t buddy_write(struct file *filp,const char __user *buf,size_t count,loff_t *offset)
{
	printk(KERN_INFO "Write device\n");
	return 0;
}
/*
 *release operation
 */
static int buddy_release(struct inode *inode,struct file *filp)
{
	printk(KERN_INFO "Release device\n");
	return 0;
}
/*
 * read operation
 */
static ssize_t buddy_read(struct file *filp,char __user *buf,size_t count,
		loff_t *offset)
{
	printk(KERN_INFO "Read device\n");
	return 0;
}
/*
 * file_operations
 */
static struct file_operations buddy_fops = {
	.owner     = THIS_MODULE,
	.open      = buddy_open,
	.release   = buddy_release,
	.write     = buddy_write,
	.read      = buddy_read,
};
/*
 * misc struct 
 */

static struct miscdevice buddy_misc = {
	.minor    = MISC_DYNAMIC_MINOR,
	.name     = DEV_NAME,
	.fops     = &buddy_fops,
};
/*
 * Init module
 */
static __init int buddy_init(void)
{
	misc_register(&buddy_misc);
	printk("buddy_test\n");
	//open_USB0();
	//open_USB1();
	return 0;
}
/*
 * Exit module
 */
static __exit void buddy_exit(void)
{
	printk(KERN_INFO "buddy_exit_module\n");
	misc_deregister(&buddy_misc);
}
/*
 * module information
 */
module_init(buddy_init);
module_exit(buddy_exit);

MODULE_LICENSE("GPL");
