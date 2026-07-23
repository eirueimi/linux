#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");

static const struct file_operations m15_fops = {
	.owner = THIS_MODULE,
};
static struct miscdevice m15_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "m15",
	.fops  = &m15_fops,
};

static int __init m15_init(void)
{
	/* TODO: misc_register(&m15_dev) で登録し、割り当てられた
	 * m15_dev.minor を "m15dev: misc registered minor=<n>" として pr_info せよ */
	return 0;
}
static void __exit m15_exit(void) { misc_deregister(&m15_dev); }

module_init(m15_init);
module_exit(m15_exit);
