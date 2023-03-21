/*
 * Name: hello-procfs.c
 * Purpose: Simple driver making use of procfs
 * Author: Ryan Agius
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>                 //kmalloc()
#include<linux/uaccess.h>              //copy_to/from_user()
#include <linux/ioctl.h>
#include<linux/proc_fs.h>
#include <linux/err.h>

#define LINUX_KERNEL_VERSION  492
 
#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

