/*
 * Name: hello_argument.c
 * Purpose: Prints hello world and goodbye cruel world as a kernel log when 
 *          initialised and deinitialised.
 *          Creates two files in /sys/module that can be interacted with
 * Author: Ryan Agius
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

int value, array_value[4];
char *string;
int cb_value = 0;

module_param(value, int, S_IRUSR|S_IWUSR);                      // integer variable, user can read and write
module_param(string, charp, S_IRUSR|S_IWUSR);                   // string variiable, user can read and write
module_param_array(array_value, int, NULL, S_IRUSR|S_IWUSR);    // array of int

int notify_param(const char *val, const struct kernel_param *kp)
{
    int res = param_set_int(val, kp);       // use a helper function to write variable
    if (res == 0) {
        pr_info("Callback function called...\n");
        pr_info("New value of cb_value = %d\n", cb_value);
        return 0;
    }
    return -1;
}

const struct kernel_param_ops my_param_ops = 
{
    .set = &notify_param,    // use our custom setter
    .get = &param_get_int,   // and the standart getter
};

module_param_cb(cb_value, &my_param_ops, &cb_value, S_IRUSR|S_IWUSR);    // register the callback


/* Module init function */
static int __init hello_world_init(void)
{
    int i;
    pr_info("Hello World!\n");
    pr_info("value = %d\n", value);
    pr_info("string = %s\n", string);
    for (i = 0; i < (sizeof array_value / sizeof (int)); i++) {
        pr_info("array_value[%d] = %d\n", i, array_value[i]);
    }

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