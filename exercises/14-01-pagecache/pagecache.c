#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/vmstat.h>   /* global_node_page_state */

MODULE_LICENSE("GPL");

static int __init m14_init(void)
{
	long nr = global_node_page_state(NR_FILE_PAGES);

	pr_info("m14cache: page_cache_pages=%ld\n", nr);
	return 0;
}
static void __exit m14_exit(void) { }

module_init(m14_init);
module_exit(m14_exit);
