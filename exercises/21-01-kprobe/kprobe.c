#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kprobes.h>

MODULE_LICENSE("GPL");

static int m21_pre(struct kprobe *p, struct pt_regs *regs)
{
	/* TODO(任意): フック発火時に "m21trace: kprobe hit on <sym>" を出してもよい */
	pr_info("m21trace: kprobe hit on %s\n", p->symbol_name);
	return 0;
}

static struct kprobe m21_kp = {
	.symbol_name = "do_sys_openat2",
	.pre_handler = m21_pre,
};

static int __init m21_init(void)
{
	/* TODO: register_kprobe(&m21_kp) で do_sys_openat2 にkprobeを仕掛け、
	 * 戻り値を "m21trace: registered ret=<r> sym=<sym>" として pr_info せよ */
	return 0;
}
static void __exit m21_exit(void)
{
	/* 登録した場合は unregister_kprobe(&m21_kp) で解除する */
}

module_init(m21_init);
module_exit(m21_exit);
