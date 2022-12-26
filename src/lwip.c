#include "link.h"
#include "dpdk.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"

struct netif g_netif;

static void
do_init(void * arg)
{
    ip4_addr_t ipaddr, netmask, gw;
    sys_sem_t *init_sem;
    LWIP_ASSERT("arg != NULL", arg != NULL);
    init_sem = (sys_sem_t*)arg;

    /* init randomizer again (seed per thread) */
    srand((unsigned int)time(NULL));

    IP4_ADDR(&ipaddr, 20, 0, 0, 20);
    IP4_ADDR(&gw, 20, 0, 0, 1);
    IP4_ADDR(&netmask, 255, 255, 255, 0);

    printf("Starting lwIP, local interface IP is %s\n", ip4addr_ntoa(&ipaddr));
	netif_add(&g_netif, &ipaddr, &netmask, &gw, &g_port_info, dpdk_device_init, ethernet_input);
	netif_set_default(&g_netif);
	netif_set_up(&g_netif);
	// netif_set_link_up(&g_netif);

    sys_sem_signal(init_sem);
}

int lwip_init_on_dpdk(int argc, char *argv[])
{
    sys_sem_t init_sem;
    int ret = 0;

    ret = sys_sem_new(&init_sem, 0);
    LWIP_ASSERT("failed to create init_sem", ret == ERR_OK);

    /* TODO, 目前报文直接在"主线程"处理，没有投递给tcpip线程 */
    tcpip_init(do_init, &init_sem);
    /* we have to wait for initialization to finish before
    * calling update_adapter()! */

    sys_sem_wait(&init_sem);
    sys_sem_free(&init_sem);

    printf("sem free\n");
    dpdk_launch();

    return ret;
}