#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>   /* for_each_process */

MODULE_LICENSE("GPL");

static int __init m2walk_init(void)
{
	struct task_struct *p;
	int n = 0;

	for_each_process(p)
		n++;

	pr_info("m2walk: process count = %d\n", n);
	return 0;
}
static void __exit m2walk_exit(void) { }

module_init(m2walk_init);
module_exit(m2walk_exit);
