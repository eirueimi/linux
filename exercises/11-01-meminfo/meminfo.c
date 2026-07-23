#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm.h>   /* si_meminfo */

MODULE_LICENSE("GPL");

static int __init m11_init(void)
{
	struct sysinfo si;

	si_meminfo(&si);
	pr_info("m11reclaim: totalram=%lu freeram=%lu (pages)\n",
		si.totalram, si.freeram);
	return 0;
}
static void __exit m11_exit(void) { }

module_init(m11_init);
module_exit(m11_exit);
