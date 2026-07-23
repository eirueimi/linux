#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

static struct kmem_cache *m9_cache;
static void *m9_obj;

static int __init m9slab_init(void)
{
	m9_cache = kmem_cache_create("m9cache", 128, 0, 0, NULL);
	if (!m9_cache)
		return -ENOMEM;
	m9_obj = kmem_cache_alloc(m9_cache, GFP_KERNEL);
	pr_info("m9slab: created and allocated\n");
	return 0;
}
static void __exit m9slab_exit(void)
{
	if (m9_obj)
		kmem_cache_free(m9_cache, m9_obj);
	if (m9_cache)
		kmem_cache_destroy(m9_cache);
}

module_init(m9slab_init);
module_exit(m9slab_exit);
