/* 
 * Copied from the Linux Kernel Programming Guide
 * hello-1.c - The simplest kernel module. 
 */ 
#include <linux/module.h> /* Needed by all modules */ 
#include <linux/printk.h> /* Needed for pr_info() */ 
 
int init_module(void) 
{ 
    pr_info("hello-world: Hello world 1.\n"); 
 
    /* A non 0 return means init_module failed; module can't be loaded. */ 
    return 0; 
} 
 
void cleanup_module(void) 
{ 
    pr_info("hello-world: Goodbye world 1.\n"); 
} 

MODULE_AUTHOR("Ryan Agius <ryagius17@gmail.com>");
MODULE_DESCRIPTION("Hello World!");
MODULE_LICENSE("GPL");