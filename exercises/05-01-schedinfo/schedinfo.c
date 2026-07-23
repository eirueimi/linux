#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int __init m5_init(void)
{
	pr_info("m5sched: policy=%u prio=%d nice=%d\n",
		current->policy, current->prio, task_nice(current));
	return 0;
}
static void __exit m5_exit(void) { }

module_init(m5_init);
module_exit(m5_exit);
