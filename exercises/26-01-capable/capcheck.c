#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/capability.h>
#include <linux/cred.h>

MODULE_LICENSE("GPL");

static int __init m26_init(void)
{
	/* TODO: capable(CAP_SYS_ADMIN) と current_uid() を取り、
	 * "m26sec: uid=<uid> CAP_SYS_ADMIN=<0/1>" として pr_info せよ
	 * （uid は __kuid_val(current_uid()) で数値化）*/
	return 0;
}
static void __exit m26_exit(void) { }

module_init(m26_init);
module_exit(m26_exit);
