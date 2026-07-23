#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <net/net_namespace.h>

MODULE_LICENSE("GPL");

static unsigned int m24_hook(void *priv, struct sk_buff *skb,
			     const struct nf_hook_state *state)
{
	return NF_ACCEPT;
}

static struct nf_hook_ops m24_ops = {
	.hook     = m24_hook,
	.pf       = NFPROTO_IPV4,
	.hooknum  = NF_INET_LOCAL_OUT,
	.priority = NF_IP_PRI_FIRST,
};

static int __init m24_init(void)
{
	/* TODO: nf_register_net_hook(&init_net, &m24_ops) でフックを登録し、
	 * 戻り値を "m24net: hook registered ret=<r>" として pr_info せよ */
	return 0;
}
static void __exit m24_exit(void)
{
	/* 登録した場合は nf_unregister_net_hook(&init_net, &m24_ops) で解除する */
}

module_init(m24_init);
module_exit(m24_exit);
