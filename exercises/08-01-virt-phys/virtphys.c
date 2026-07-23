#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/io.h>   /* virt_to_phys */

MODULE_LICENSE("GPL");

static int __init m8_init(void)
{
	void *p = kmalloc(64, GFP_KERNEL);
	if (!p)
		return -ENOMEM;
	/* TODO: p の仮想アドレスと virt_to_phys(p) の物理アドレスを
	 * "m8addr: va=0x<va> pa=0x<pa>" として pr_info せよ（%px と %llx）*/
	kfree(p);
	return 0;
}
static void __exit m8_exit(void) { }

module_init(m8_init);
module_exit(m8_exit);
