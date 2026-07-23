#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/namei.h>   /* kern_path */
#include <linux/fs.h>
#include <linux/dcache.h>

MODULE_LICENSE("GPL");

static int __init m12_init(void)
{
	struct path p;
	/* TODO: kern_path("/proc", LOOKUP_FOLLOW, &p) でパス探索し、
	 * inode 番号 d_inode(p.dentry)->i_ino と スーパーブロックの s_magic を
	 * "m12vfs: /proc ino=<n> sb_magic=0x<magic>" として pr_info、最後に path_put(&p) */
	(void)p;
	return 0;
}
static void __exit m12_exit(void) { }

module_init(m12_init);
module_exit(m12_exit);
