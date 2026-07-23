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
	int r = misc_register(&m15_dev);

	if (r) {
		pr_info("m15dev: register failed %d\n", r);
		return r;
	}
	pr_info("m15dev: misc registered minor=%d\n", m15_dev.minor);
	return 0;
}
static void __exit m15_exit(void) { misc_deregister(&m15_dev); }

module_init(m15_init);
module_exit(m15_exit);
