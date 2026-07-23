#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

static int __init m7_init(void)
{
	unsigned long t0 = jiffies;
	msleep(100);
	pr_info("m7time: HZ=%d jiffies=%lu delta=%lu\n",
		HZ, jiffies, jiffies - t0);
	return 0;
}
static void __exit m7_exit(void) { }

module_init(m7_init);
module_exit(m7_exit);
