/*
 * Name: hello_device_driver.c
 * Purpose: Simple char device driver
 * Author: Ryan Agius
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/device.h>

#define MINOR_NUM_MIN 42

// create a dummy device (to be updated dynamically)
dev_t dev = 0;

// struct class definition for the device
static struct class *dev_class;


/* Module init function */
static int __init hello_module_init(void)
{
    /* Allocate a MAJOR number */
    if ((alloc_chrdev_region(&dev, MINOR_NUM_MIN, 1, "ryagi")) < 0) {
        pr_err("Cannot allocate major number for device 1");
        return -1;
    }

    /* Creating the struct class*/
    dev_class = class_create(THIS_MODULE, "ryagi_class");
    if (IS_ERR(dev_class)) {
            pr_err("Cannot create the struct class for device\n");
            goto r_class;
    }

    /* Create the device that inherits from the class */
    if (IS_ERR(device_create(dev_class, NULL, dev, NULL, "ryagi_device"))) {
        pr_err("Cannot create the device\n");
            goto r_device;
    }

    pr_info("Kernel module inserted successfully with MAJOR:MINOR %d:%d\n", MAJOR(dev), MINOR(dev));
    return 0;

    r_device:
        class_destroy(dev_class);
    r_class:
        unregister_chrdev_region(dev, 1);
        return -1;
}

/* Module exit function */
static void __exit hello_module_exit(void)
{
    unregister_chrdev_region(dev, 1);
    pr_info("Kernel module removed successfully...\n");
}

module_init(hello_module_init);
module_exit(hello_module_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ryan Agius");
MODULE_DESCRIPTION("Simple linux driver to automatically create device file in /sys/class");
MODULE_VERSION("2:1:0");