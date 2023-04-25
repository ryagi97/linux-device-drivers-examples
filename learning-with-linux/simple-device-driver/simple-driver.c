/*
 * Name: simple-driver.c
 * Purpose: Simple device driver, without hardware
 * Author: Ryan Agius
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

// kernel memoory size
#define mem_size 1024

// device major and minor numbers
#define MINOR_NUM_MIN 42

dev_t dev = 0;

static struct class *dev_class;
static struct cdev my_cdev;

uint8_t *kernel_buffer;

/* Function prototypes */
static int      __init my_driver_init(void);
static void     __exit my_driver_exit(void);
static int      my_open(struct inode *inode, struct file *file);
static int      my_release(struct inode *inode, struct file *file);
static ssize_t  my_read(struct file *filep, char __user *buf, size_t len, loff_t *off);
static ssize_t  my_write(struct file *filep, const char *buf, size_t len, loff_t *off);

static struct file_operations fops = {
    .owner      = THIS_MODULE,
    .read       = my_read,
    .write      = my_write,
    .open       = my_open,
    .release    = my_release,
};

/* funcion called when device (file) is opened */
static int my_open(struct inode *inode, struct file *file)
{
    pr_info("Device file opened\n");
    return 0;
}

/* funcion called when device (file) is released */
static int my_release(struct inode *inode, struct file *file)
{
    pr_info("Device file released\n");
    return 0;
}

/* funcion called when device (file) is read from */
static ssize_t my_read(struct file *filep, char __user *buf, size_t len, loff_t *off)
{   
    
    if (copy_to_user(buf, kernel_buffer, len))
        pr_err("Data read error!\n");

    pr_info("Device file read from...\n");
    return mem_size;
}

/* funcion called when device (file) is written to */
static ssize_t my_write(struct file *filep, const char *buf, size_t len, loff_t *off)
{
    /* Copy from user space to kernel space */
    if (copy_from_user(kernel_buffer, buf, mem_size))
        pr_err("Data write error!\n");

    pr_info("Device file written to...\n");
    return len;
}


/* Module init function */
static int __init my_driver_init(void)
{
    /* Allocate a MAJOR number */
    if ((alloc_chrdev_region(&dev, MINOR_NUM_MIN, 1, "my_Dev")) < 0) {
        pr_err("Cannot allocate device");
        return -1;
    }
    pr_info("Kernel module inserted successfully with MAJOR:MINOR %d:%d\n", MAJOR(dev), MINOR(dev));

    /* cdev structure (part of inodes) */
    cdev_init(&my_cdev, &fops);

    /* add 1 char device to system */
    if (cdev_add(&my_cdev, dev, 1) < 0) {
        pr_err("Cannot add device to system\n");
        goto r_class;
    }

    /* create the struct class */
    if (IS_ERR(dev_class = class_create(THIS_MODULE, "my_class"))) {
        pr_err("Cannot create the struct class\n");
        goto r_class;    
    }

    /* create the device */
    if (IS_ERR(device_create(dev_class, NULL, dev, NULL, "my_device"))) {
        pr_err("Cannot create the struct class");
        goto r_device;    
    }

    /* Allocate physical memory for the file and its contents */
    if ((kernel_buffer = kmalloc(mem_size, GFP_KERNEL)) == 0) {
        pr_err("Cannot allocate memory in kernel space!\n");
        goto r_device;
    }

    /* Initialise the buffer with some data */
    strcpy(kernel_buffer, "TRIAL");

    pr_info("Device driver inserted!\n");
    return 0;

r_device:
    class_destroy(dev_class);
r_class:
    unregister_chrdev_region(dev, 1);
    return -1;
}

/* Module exit function */
static void __exit my_driver_exit(void)
{
    kfree(kernel_buffer);
    device_destroy(dev_class, dev);
    class_destroy(dev_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev, 1);
    pr_info("Device driver removed successfully...\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ryan Agius");
MODULE_DESCRIPTION("Simple Linux device driver");
MODULE_VERSION("2:1:0");