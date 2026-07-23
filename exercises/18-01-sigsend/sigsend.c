#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched/signal.h>   /* send_sig, signal_pending */

MODULE_LICENSE("GPL");

static int __init m18_init(void)
{
	int r = send_sig(SIGCONT, current, 0);

	pr_info("m18sig: send_sig(SIGCONT) ret=%d signal_pending=%d\n",
		r, signal_pending(current));
	return 0;
}
static void __exit m18_exit(void) { }

module_init(m18_init);
module_exit(m18_exit);
