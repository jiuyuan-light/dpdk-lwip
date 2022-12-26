#ifndef __DPDK_LWIP_LINK_H__
#define __DPDK_LWIP_LINK_H__

#include <rte_ethdev.h>
#include <rte_common.h>

#include "lwip/tcpip.h"
#include "netif/etharp.h"

struct port_info_t {
	int port;
	struct rte_mempool* pktmbuf_pool;
	struct rte_ether_addr src_addr;
};

extern struct port_info_t g_port_info;
extern struct netif g_netif;

err_t
dpdk_device_init(struct netif *nif);
int init_port(int port);

err_t
dpdk_input(struct rte_mbuf* m, struct netif *nif);

#endif /* __DPDK_LWIP_LINK_H__ */