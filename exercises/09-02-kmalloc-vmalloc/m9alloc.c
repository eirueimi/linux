#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

MODULE_LICENSE("GPL");

static void *m9_kbuf;
static void *m9_vbuf;

static int __init m9alloc_init(void)
{
	/* TODO: m9_kbuf = kmalloc(1024, GFP_KERNEL)、m9_vbuf = vmalloc(1024) で
	 * それぞれ確保し、"m9alloc: kmalloc=%px vmalloc=%px" の形式で pr_info せよ */
	return 0;
}
static void __exit m9alloc_exit(void)
{
	kfree(m9_kbuf);
	vfree(m9_vbuf);
}

module_init(m9alloc_init);
module_exit(m9alloc_exit);
