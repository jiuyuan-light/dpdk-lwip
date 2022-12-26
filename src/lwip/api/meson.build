api_srcs = [
    'api_lib.c',
    'api_msg.c',
    'err.c',
    'if_api.c',
    'netbuf.c',
    'netdb.c',
    'netifapi.c',
    'sockets.c',
    'tcpip.c',
]

path_srcs = []
foreach src:api_srcs
    src = 'lwip/api/' + src
    path_srcs += src
endforeach


lwip_srcs += path_srcs