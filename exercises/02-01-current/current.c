#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int __init m2cur_init(void)
{
	pr_info("m2cur: current: %s (pid %d)\n", current->comm, current->pid);
	return 0;
}
static void __exit m2cur_exit(void) { }

module_init(m2cur_init);
module_exit(m2cur_exit);
