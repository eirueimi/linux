#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int __init m10_init(void)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;
	int n = 0;

	if (!mm) {
		pr_info("m10vma: current has no mm\n");
		return 0;
	}
	{
		VMA_ITERATOR(vmi, mm, 0);
		mmap_read_lock(mm);
		for_each_vma(vmi, vma)
			n++;
		mmap_read_unlock(mm);
	}
	pr_info("m10vma: vma count=%d\n", n);
	return 0;
}
static void __exit m10_exit(void) { }

module_init(m10_init);
module_exit(m10_exit);
