/*
 * Copyright (c) 2011 Felix Fietkau <nbd@openwrt.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/rtnetlink.h>
#include <linux/pkt_cls.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <net/netlink.h>
#include <net/pkt_sched.h>
#include <net/act_api.h>

#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_core.h>

#define TCA_ACT_CONNMARK	20

#define CONNMARK_TAB_MASK     3

static struct tcf_hashinfo connmark_hash_info;

static int tcf_connmark(struct sk_buff *skb, const struct tc_action *a,
		       struct tcf_result *res)
{
	struct nf_conn *c;
	enum ip_conntrack_info ctinfo;
	int proto;
	int r;

	if (skb->protocol == htons(ETH_P_IP)) {
		if (skb->len < sizeof(struct iphdr))
			goto out;
		proto = PF_INET;
	} else if (skb->protocol == htons(ETH_P_IPV6)) {
		if (skb->len < sizeof(struct ipv6hdr))
			goto out;
		proto = PF_INET6;
	} else
		goto out;

	r = nf_conntrack_in(dev_net(skb->dev), proto, NF_INET_PRE_ROUTING, skb);
	if (r != NF_ACCEPT)
		goto out;

	c = nf_ct_get(skb, &ctinfo);
	if (!c)
		goto out;

	skb->mark = c->mark;
	nf_conntrack_put(skb->nfct);
	skb->nfct = NULL;

out:
	return TC_ACT_PIPE;
}

static int tcf_connmark_init(struct net *net, struct nlattr *nla,
			     struct nlattr *est, struct tc_action *a,
			     int ovr, int bind)
{
	struct tcf_common *pc;
	int ret = 0;

	pc = tcf_hash_check(0, a, bind);
	if (!pc) {
		pc = tcf_hash_create(0, est, a, sizeof(*pc), bind);
		if (IS_ERR(pc))
		    return PTR_ERR(pc);

		tcf_hash_insert(pc, a->ops->hinfo);
		ret = ACT_P_CREATED;
	} else {
		if (!ovr) {
			tcf_hash_release(pc, bind, a->ops->hinfo);
			return -EEXIST;
		}
	}
 

	return ret;
}

static inline int tcf_connmark_cleanup(struct tc_action *a, int bind)
{
	if (a->priv)
		return tcf_hash_release(a->priv, bind, a->ops->hinfo);
	return 0;
}

static inline int tcf_connmark_dump(struct sk_buff *skb, struct tc_action *a,
				int bind, int ref)
{
	return skb->len;
}

static struct tc_action_ops act_connmark_ops = {
	.kind		=	"connmark",
	.hinfo		=	&connmark_hash_info,
	.type		=	TCA_ACT_CONNMARK,
	.owner		=	THIS_MODULE,
	.act		=	tcf_connmark,
	.dump		=	tcf_connmark_dump,
	.cleanup	=	tcf_connmark_cleanup,
	.init		=	tcf_connmark_init,
};

MODULE_AUTHOR("Felix Fietkau <nbd@openwrt.org>");
MODULE_DESCRIPTION("Connection tracking mark restoring");
MODULE_LICENSE("GPL");

static int __init connmark_init_module(void)
{
	int err = tcf_hashinfo_init(&connmark_hash_info, CONNMARK_TAB_MASK);
	if (err)
		return err;

	return tcf_register_action(&act_connmark_ops);
}

static void __exit connmark_cleanup_module(void)
{
	tcf_unregister_action(&act_connmark_ops);
}

module_init(connmark_init_module);
module_exit(connmark_cleanup_module);
