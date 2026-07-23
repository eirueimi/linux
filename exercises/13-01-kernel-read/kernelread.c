#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>   /* filp_open, kernel_read, filp_close */

MODULE_LICENSE("GPL");

static int __init m13_init(void)
{
	/* TODO: filp_open("/proc/version", O_RDONLY, 0) で開き、
	 * kernel_read() で先頭を読み、"m13file: read=<n> first=<先頭5文字>" を pr_info、
	 * 最後に filp_close()。IS_ERR() でエラーチェックすること */
	return 0;
}
static void __exit m13_exit(void) { }

module_init(m13_init);
module_exit(m13_exit);
