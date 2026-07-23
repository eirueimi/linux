#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm.h>   /* si_meminfo */

MODULE_LICENSE("GPL");

static int __init m11_init(void)
{
	struct sysinfo si;

	/* TODO: si_meminfo(&si) で総ページ数と空きページ数を取り、
	 * "m11reclaim: totalram=<n> freeram=<n> (pages)" を pr_info せよ */
	(void)si;
	return 0;
}
static void __exit m11_exit(void) { }

module_init(m11_init);
module_exit(m11_exit);
