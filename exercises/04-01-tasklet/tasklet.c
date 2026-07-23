#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>   /* tasklet */
#include <linux/delay.h>       /* msleep */

MODULE_LICENSE("GPL");

static void m4_fn(struct tasklet_struct *t)
{
	pr_info("m4tasklet: softirq context in_softirq=%lu\n", in_softirq());
}
static DECLARE_TASKLET(m4_task, m4_fn);

static int __init m4_init(void)
{
	tasklet_schedule(&m4_task);
	msleep(100);            /* softirq を確実に走らせてから戻る */
	return 0;
}
static void __exit m4_exit(void) { tasklet_kill(&m4_task); }

module_init(m4_init);
module_exit(m4_exit);
