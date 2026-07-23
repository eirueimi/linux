#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int __init m2cur_init(void)
{
	/* TODO: 現在のプロセスの名前(current->comm)とPID(current->pid)を
	 * "m2cur: current: <名前> (pid <PID>)" の形式で pr_info せよ */
	return 0;
}
static void __exit m2cur_exit(void) { }

module_init(m2cur_init);
module_exit(m2cur_exit);
