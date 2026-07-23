#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>   /* filp_open, kernel_read, filp_close */

MODULE_LICENSE("GPL");

static int __init m13_init(void)
{
	struct file *f = filp_open("/proc/version", O_RDONLY, 0);
	char buf[64];
	loff_t pos = 0;
	ssize_t n;

	if (IS_ERR(f)) {
		pr_info("m13file: open failed %ld\n", PTR_ERR(f));
		return 0;
	}
	n = kernel_read(f, buf, sizeof(buf) - 1, &pos);
	if (n > 0) {
		buf[n] = '\0';
		pr_info("m13file: read=%zd first=%.5s\n", n, buf);
	}
	filp_close(f, NULL);
	return 0;
}
static void __exit m13_exit(void) { }

module_init(m13_init);
module_exit(m13_exit);
