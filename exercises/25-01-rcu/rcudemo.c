#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/rcupdate.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

struct m25_data {
	int val;
	struct rcu_head rcu;
};
static struct m25_data __rcu *m25_ptr;

static void m25_free(struct rcu_head *head)
{
	struct m25_data *d = container_of(head, struct m25_data, rcu);

	pr_info("m25rcu: callback freed val=%d\n", d->val);
	kfree(d);
}

static int __init m25_init(void)
{
	struct m25_data *d = kmalloc(sizeof(*d), GFP_KERNEL);
	struct m25_data *old;

	if (!d)
		return -ENOMEM;
	d->val = 42;
	rcu_assign_pointer(m25_ptr, d);

	rcu_read_lock();
	old = rcu_dereference(m25_ptr);
	pr_info("m25rcu: reader saw val=%d\n", old ? old->val : -1);
	rcu_read_unlock();

	old = rcu_dereference_protected(m25_ptr, 1);
	rcu_assign_pointer(m25_ptr, NULL);
	call_rcu(&old->rcu, m25_free);
	rcu_barrier();   /* コールバック完了まで待つ */
	return 0;
}
static void __exit m25_exit(void) { }

module_init(m25_init);
module_exit(m25_exit);
