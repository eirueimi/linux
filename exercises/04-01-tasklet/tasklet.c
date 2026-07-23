#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>   /* tasklet */
#include <linux/delay.h>       /* msleep */

MODULE_LICENSE("GPL");

static void m4_fn(struct tasklet_struct *t)
{
	/* TODO: "m4tasklet: softirq context in_softirq=<値>" を pr_info せよ
	 * （in_softirq() の戻り値を使う） */
}
static DECLARE_TASKLET(m4_task, m4_fn);

static int __init m4_init(void)
{
	/* TODO: tasklet_schedule() でタスクレットを予約し、msleep(100) で
	 * softirq が走るのを待ってから return せよ */
	return 0;
}
static void __exit m4_exit(void) { tasklet_kill(&m4_task); }

module_init(m4_init);
module_exit(m4_exit);
