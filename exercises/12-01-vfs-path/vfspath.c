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
	int err = kern_path("/proc", LOOKUP_FOLLOW, &p);

	if (err) {
		pr_info("m12vfs: kern_path failed %d\n", err);
		return 0;
	}
	pr_info("m12vfs: /proc ino=%lu sb_magic=0x%lx\n",
		d_inode(p.dentry)->i_ino,
		(unsigned long)p.dentry->d_sb->s_magic);
	path_put(&p);
	return 0;
}
static void __exit m12_exit(void) { }

module_init(m12_init);
module_exit(m12_exit);
