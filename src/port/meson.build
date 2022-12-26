port_srcs = [
    'sys_arch.c',
    'perf.c',


    'netif/tapif.c',
    'netif/list.c',
    'netif/sio.c',
    'netif/fifo.c'
]

path_srcs = []
foreach src:port_srcs
    src = 'port/' + src
    path_srcs += src
endforeach


lwip_srcs += path_srcs