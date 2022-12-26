#include "link.h"

#define RX_RING_SIZE       128
#define TX_RING_SIZE       128

#define NUM_MBUFS          (1024 - 1)   /* 1K */
#define MBUF_CACHE_SIZE    512
#define MAX_RX_PKT_BURST   64

struct port_info_t g_port_info;

err_t
dpdk_input(struct rte_mbuf* m, struct netif *nif)
{
	err_t ret;
	struct pbuf *p;
	uint16_t len;

//	printf("DPDK  IN:Packet in %d \n", m->pkt_len);

	len = m->pkt_len;
	p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);

	if(p == NULL){
		pbuf_free(p); /*memp uses an array with varying size interval inside the array to allocate memory (this array is in heap), seems to just reset the index so that the array can be written over*/
		rte_pktmbuf_free(m);
		printf("Packet Dropped\n");
		return ERR_BUF;
	}
//	decode_ip_pkt(rte_pktmbuf_mtod(m, void *));

//	p->payload = rte_pktmbuf_mtod(m, void *);
	rte_memcpy(p->payload, rte_pktmbuf_mtod(m, void *), len);

    LOCK_TCPIP_CORE();
	ret = nif->input(p, nif);
    UNLOCK_TCPIP_CORE();
	if(ret != ERR_OK){
		printf("input err\n");
		pbuf_free(p);
	}

	rte_pktmbuf_free(m);

	return ret;
}

static err_t
dpdk_output(struct netif *nif, struct pbuf *p)
{
	struct port_info_t *port_info = (struct port_info_t *)nif->state;
	struct rte_mbuf *mbuf;
	struct pbuf *q;
	uint16_t offset;

	mbuf = rte_pktmbuf_alloc(port_info->pktmbuf_pool);

	if (!mbuf) {
		rte_exit(EXIT_FAILURE, "rte_pktmbuf_alloc\n");
	}
	mbuf->pkt_len = p->tot_len;
	mbuf->data_len = p->tot_len;
	offset = 0;

	for(q = p; q != NULL; q = q->next) {
//		printf("DPDK OUT: p->tot_len %d p->len %d p->type %d\n", q->tot_len, q->len, q->type_internal);
		rte_memcpy(rte_pktmbuf_mtod_offset(mbuf, void *, offset), q->payload, q->len);
		offset += q->len;
	}
//	decode_ip_pkt(rte_pktmbuf_mtod(mbuf, void *));

	rte_eth_tx_burst(0, 0, &mbuf, 1);
	rte_pktmbuf_free(mbuf);
	rte_delay_us(25);

	printf("DPDK OUT: p %p p->tot_len %d p->len %d p->type %d\n",p, p->tot_len, p->len, p->type_internal);

	return 0;
}

err_t
dpdk_device_init(struct netif *nif)
{
	struct port_info_t *port_info = (struct port_info_t *)nif->state;

	nif->name[0] = 'd';
	nif->name[1] = 'k';
	nif->output = etharp_output;
	nif->linkoutput = dpdk_output;
	nif->mtu = 1500;
	nif->hwaddr_len = 6;
	nif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_IGMP | NETIF_FLAG_ETHARP;

	nif->hwaddr[0] = port_info->src_addr.addr_bytes[0];
	nif->hwaddr[1] = port_info->src_addr.addr_bytes[1];
	nif->hwaddr[2] = port_info->src_addr.addr_bytes[2];
	nif->hwaddr[3] = port_info->src_addr.addr_bytes[3];
	nif->hwaddr[4] = port_info->src_addr.addr_bytes[4];
	nif->hwaddr[5] = port_info->src_addr.addr_bytes[5];

	return ERR_OK;

}
