#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello world kernel module");

static int __init hello_init(void)
{
	/* TODO: dmesg に "hello: loaded" を出力し、0 を返す */
	return 0;
}

static void __exit hello_exit(void)
{
	/* TODO: dmesg に "hello: unloaded" を出力する */
}

module_init(hello_init);
module_exit(hello_exit);
