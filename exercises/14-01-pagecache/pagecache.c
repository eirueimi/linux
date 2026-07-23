#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/vmstat.h>   /* global_node_page_state */

MODULE_LICENSE("GPL");

static int __init m14_init(void)
{
	/* TODO: global_node_page_state(NR_FILE_PAGES) でページキャッシュの
	 * ページ数を取り、"m14cache: page_cache_pages=<n>" を pr_info せよ */
	return 0;
}
static void __exit m14_exit(void) { }

module_init(m14_init);
module_exit(m14_exit);
