#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched/signal.h>   /* send_sig, signal_pending */

MODULE_LICENSE("GPL");

static int __init m18_init(void)
{
	/* TODO: send_sig(SIGCONT, current, 0) で current にシグナルを送り、
	 * 戻り値と signal_pending(current) を
	 * "m18sig: send_sig(SIGCONT) ret=<r> signal_pending=<p>" として pr_info せよ */
	return 0;
}
static void __exit m18_exit(void) { }

module_init(m18_init);
module_exit(m18_exit);
