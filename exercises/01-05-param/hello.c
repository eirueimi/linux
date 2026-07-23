#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static char *name = "world";
module_param(name, charp, 0444);
MODULE_PARM_DESC(name, "name to greet");

static int __init hello_init(void)
{
	pr_info("hello: hello, %s\n", name);
	return 0;
}

static void __exit hello_exit(void) { pr_info("hello: bye\n"); }

module_init(hello_init);
module_exit(hello_exit);
