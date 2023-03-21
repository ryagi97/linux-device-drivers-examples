/*
 * Name: hello_driver.c
 * Purpose: Prints hello world and goodbye cruel world as a kernel log when 
 *          initialised and deinitialised
 * Author: Ryan Agius
 */

#include <linux/module.h>

/* Module init function */
static int __init hello_world_init(void)
{
    pr_info("Hello World!\n");
    pr_info("Kernel module inserted successfully...\n");
    return 0;
}

/* Module exit function */
static void __exit hello_world_exit(void)
{
    pr_info("Goodbye Cruel World!\n");
    pr_info("Kernel module removed successfully...\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ryan Agius");
MODULE_DESCRIPTION("Hello World!");
MODULE_VERSION("2:1:0");