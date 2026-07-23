#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int __init m2parent_init(void)
{
	struct task_struct *p = current;

	pr_info("m2parent: chain start\n");
	while (p->pid != 0) {
		pr_info("m2parent: %s (pid %d)\n", p->comm, p->pid);
		if (p->pid == 1)
			break;
		p = p->real_parent;
	}
	pr_info("m2parent: reached pid 1\n");
	return 0;
}
static void __exit m2parent_exit(void) { }

module_init(m2parent_init);
module_exit(m2parent_exit);
