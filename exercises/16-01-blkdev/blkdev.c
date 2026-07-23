#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/blkdev.h>   /* register_blkdev */

MODULE_LICENSE("GPL");

static int m16_major;

static int __init m16_init(void)
{
	/* TODO: register_blkdev(0, "m16") で動的メジャー番号を取得し、
	 * "m16blk: registered major=<n>" を pr_info せよ（<=0 はエラー） */
	return 0;
}
static void __exit m16_exit(void) { unregister_blkdev(m16_major, "m16"); }

module_init(m16_init);
module_exit(m16_exit);
