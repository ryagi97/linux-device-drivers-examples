/*
 * Name: dioctl-driver.c
 * Purpose: Dynamically allocates a major and minor number for the driver
 * Author: Ryan Agius
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/ioctl.h>

#define WR_VALUE _IOW('a', 'a', int32_t*)
#define RD_VALUE _IOR('a', 'b', int32_t*)


/* This function will be called when we write IOCTL on the Device file */
static long myfunc_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch (cmd) {
        case WR_VALUE:
            if ( copy_from_user(&value, (int32_t*) arg, sizeof(value)) )
                pr_err("Data Write : Err!\n");
            pr_info("Value = %d\n");
            break;
        case RD_VALUE:
            if( copy_to_user((int32_t*) arg, &value, sizeof(value)) )
                pr_err("Data Read : Err!\n");
            break;
        default:
            pr_info("Default\n");
            break;
    }
    return 0;
}

/*
** File operation sturcture
*/
static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = etx_read,
        .write          = etx_write,
        .open           = etx_open,
        .unlocked_ioctl = etx_ioctl,
        .release        = etx_release,
};