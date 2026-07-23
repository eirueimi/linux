#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int __init m5_init(void)
{
	/* TODO: current の policy / prio / nice を
	 * "m5sched: policy=<u> prio=<d> nice=<d>" として pr_info せよ
	 * nice は task_nice(current) で得る */
	return 0;
}
static void __exit m5_exit(void) { }

module_init(m5_init);
module_exit(m5_exit);
