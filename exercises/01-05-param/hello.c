#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

/* TODO: 文字列パラメータ name（既定 "world"）を module_param で公開する */
static char *name = "world";

static int __init hello_init(void)
{
	/* TODO: dmesg に "hello: hello, <name>" を出力する */
	return 0;
}

static void __exit hello_exit(void) { pr_info("hello: bye\n"); }

module_init(hello_init);
module_exit(hello_exit);
