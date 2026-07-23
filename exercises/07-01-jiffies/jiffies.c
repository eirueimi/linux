#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

static int __init m7_init(void)
{
	/* TODO: 開始時の jiffies を記録し、msleep(100) 後に
	 * "m7time: HZ=<HZ> jiffies=<現在> delta=<経過>" を pr_info せよ */
	return 0;
}
static void __exit m7_exit(void) { }

module_init(m7_init);
module_exit(m7_exit);
