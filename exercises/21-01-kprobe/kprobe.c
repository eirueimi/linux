#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kprobes.h>

MODULE_LICENSE("GPL");

static int m21_pre(struct kprobe *p, struct pt_regs *regs)
{
	pr_info("m21trace: kprobe hit on %s\n", p->symbol_name);
	return 0;
}

static struct kprobe m21_kp = {
	.symbol_name = "do_sys_openat2",
	.pre_handler = m21_pre,
};

static int __init m21_init(void)
{
	int r = register_kprobe(&m21_kp);

	pr_info("m21trace: registered ret=%d sym=%s\n", r, m21_kp.symbol_name);
	return 0;
}
static void __exit m21_exit(void)
{
	unregister_kprobe(&m21_kp);
}

module_init(m21_init);
module_exit(m21_exit);
