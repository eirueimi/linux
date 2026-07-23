#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/blkdev.h>   /* register_blkdev */

MODULE_LICENSE("GPL");

static int m16_major;

static int __init m16_init(void)
{
	m16_major = register_blkdev(0, "m16");
	if (m16_major <= 0) {
		pr_info("m16blk: register failed %d\n", m16_major);
		return -EIO;
	}
	pr_info("m16blk: registered major=%d\n", m16_major);
	return 0;
}
static void __exit m16_exit(void) { unregister_blkdev(m16_major, "m16"); }

module_init(m16_init);
module_exit(m16_exit);
