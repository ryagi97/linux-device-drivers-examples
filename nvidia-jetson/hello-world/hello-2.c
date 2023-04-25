/* 
 * Copied from the Linux Kernel Programming Guide
 * hello-2.c - Demonstrating the module_init() and module_exit() macros. 
 * This is preferred over using init_module() and cleanup_module(). 
 */ 
#include <linux/init.h> /* Needed for the macros */ 
#include <linux/module.h> /* Needed by all modules */ 
#include <linux/printk.h> /* Needed for pr_info() */ 
 
static int __init hello_2_init(void) 
{ 
    pr_info("hello-world: Hello, world 2\n"); 
    return 0; 
} 
 
static void __exit hello_2_exit(void) 
{ 
    pr_info("hello-world: Goodbye, world 2\n"); 
} 
 
module_init(hello_2_init); 
module_exit(hello_2_exit); 

MODULE_AUTHOR("Ryan Agius <ryagius17@gmail.com>");
MODULE_DESCRIPTION("Hello World!");
MODULE_LICENSE("GPL");