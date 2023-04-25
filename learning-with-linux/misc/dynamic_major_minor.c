/*
 * Name: dynamic_major_minor.c
 * Purpose: Dynamically allocates a major and minor number for the driver
 * Author: Ryan Agius
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

#define MINOR_NUM_MIN 42

// create a device with our selected major and minor numbers
dev_t dev = 0;

/* Module init function */
static int __init hello_module_init(void)
{
    /* Allocate a MAJOR number */
    if ((alloc_chrdev_region(&dev, MINOR_NUM_MIN, 1, "ryagi")) < 0) {
        pr_err("Cannot allocate major number for device 1");
        return -1;
    }
    pr_info("Kernel module inserted successfully with MAJOR:MINOR %d:%d\n", MAJOR(dev), MINOR(dev));
    return 0;
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
MODULE_DESCRIPTION("Hello World!");
MODULE_VERSION("2:1:0");