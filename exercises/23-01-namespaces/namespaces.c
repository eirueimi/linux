#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/pid_namespace.h>

MODULE_LICENSE("GPL");

static int __init m23_init(void)
{
	/* TODO: task_active_pid_ns(current) で current のPID名前空間を取り、
	 * その入れ子レベル ->level を "m23ns: pid_ns_level=<n>" として pr_info せよ */
	return 0;
}
static void __exit m23_exit(void) { }

module_init(m23_init);
module_exit(m23_exit);
