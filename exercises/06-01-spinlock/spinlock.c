#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/spinlock.h>

MODULE_LICENSE("GPL");

static DEFINE_SPINLOCK(m6_lock);
static int m6_counter;

static int __init m6_init(void)
{
	int i;
	for (i = 0; i < 1000; i++) {
		spin_lock(&m6_lock);
		m6_counter++;
		spin_unlock(&m6_lock);
	}
	pr_info("m6sync: counter=%d\n", m6_counter);
	return 0;
}
static void __exit m6_exit(void) { }

module_init(m6_init);
module_exit(m6_exit);
