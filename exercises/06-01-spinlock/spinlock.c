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
	/* TODO: spin_lock/spin_unlock で m6_counter を保護しながら
	 * 1000回インクリメントし、"m6sync: counter=<値>" を pr_info せよ */
	return 0;
}
static void __exit m6_exit(void) { }

module_init(m6_init);
module_exit(m6_exit);
