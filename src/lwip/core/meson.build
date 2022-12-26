core_srcs = [
    'init.c',
    'def.c',
    'dns.c',
    'inet_chksum.c',
    'ip.c',
    'mem.c',
    'memp.c',
    'netif.c',
    'pbuf.c',
    'raw.c',
    'stats.c',
    'sys.c',
    'altcp.c',
    'altcp_alloc.c',
    'altcp_tcp.c',
    'tcp.c',
    'tcp_in.c',
    'tcp_out.c',
    'timeouts.c',
    'udp.c',

    'ipv4/acd.c',
    'ipv4/autoip.c',
    'ipv4/dhcp.c',
    'ipv4/etharp.c',
    'ipv4/icmp.c',
    'ipv4/igmp.c',
    'ipv4/ip4_frag.c',
    'ipv4/ip4.c',
    'ipv4/ip4_addr.c',

    'ipv6/dhcp6.c',
    'ipv6/ethip6.c',
    'ipv6/icmp6.c',
    'ipv6/inet6.c',
    'ipv6/ip6.c',
    'ipv6/ip6_addr.c',
    'ipv6/ip6_frag.c',
    'ipv6/mld6.c',
    'ipv6/nd6.c'
]

path_srcs = []
foreach src:core_srcs
    src = 'lwip/core/' + src
    path_srcs += src
endforeach


lwip_srcs += path_srcs