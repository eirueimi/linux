#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>   /* for_each_process */

MODULE_LICENSE("GPL");

static int __init m2walk_init(void)
{
	/* TODO: for_each_process() で全プロセスを数え、
	 * "m2walk: process count = <数>" を pr_info せよ */
	return 0;
}
static void __exit m2walk_exit(void) { }

module_init(m2walk_init);
module_exit(m2walk_exit);
