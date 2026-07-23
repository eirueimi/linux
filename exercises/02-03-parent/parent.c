#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int __init m2parent_init(void)
{
	/* TODO: current から real_parent を辿り、pid 1 に達するまで
	 * 各段の comm/pid を pr_info し、最後に "m2parent: reached pid 1" を出せ */
	return 0;
}
static void __exit m2parent_exit(void) { }

module_init(m2parent_init);
module_exit(m2parent_exit);
