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
	pr_info("m8addr: va=0x%px pa=0x%llx\n",
		p, (unsigned long long)virt_to_phys(p));
	kfree(p);
	return 0;
}
static void __exit m8_exit(void) { }

module_init(m8_init);
module_exit(m8_exit);
