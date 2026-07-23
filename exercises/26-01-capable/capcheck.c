#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/capability.h>
#include <linux/cred.h>

MODULE_LICENSE("GPL");

static int __init m26_init(void)
{
	bool admin = capable(CAP_SYS_ADMIN);
	kuid_t uid = current_uid();

	pr_info("m26sec: uid=%u CAP_SYS_ADMIN=%d\n", __kuid_val(uid), admin);
	return 0;
}
static void __exit m26_exit(void) { }

module_init(m26_init);
module_exit(m26_exit);
