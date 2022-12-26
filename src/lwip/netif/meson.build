netif_srcs = [
    'ethernet.c',
	'bridgeif.c',
	'bridgeif_fdb.c',

    'ppp/auth.c',
	'ppp/ccp.c',
	'ppp/chap-md5.c',
	'ppp/chap_ms.c',
	'ppp/chap-new.c',
	'ppp/demand.c',
	'ppp/eap.c',
	'ppp/ecp.c',
	'ppp/eui64.c',
	'ppp/fsm.c',
	'ppp/ipcp.c',
	'ppp/ipv6cp.c',
	'ppp/lcp.c',
	'ppp/magic.c',
	'ppp/mppe.c',
	'ppp/multilink.c',
	'ppp/ppp.c',
	'ppp/pppapi.c',
	'ppp/pppcrypt.c',
	'ppp/pppoe.c',
	'ppp/pppol2tp.c',
	'ppp/pppos.c',
	'ppp/upap.c',
	'ppp/utils.c',
	'ppp/vj.c',
	'ppp/polarssl/arc4.c',
	'ppp/polarssl/des.c',
	'ppp/polarssl/md4.c',
	'ppp/polarssl/md5.c',
	'ppp/polarssl/sha1.c'
]

path_srcs = []
foreach src:netif_srcs
    src = 'lwip/netif/' + src
    path_srcs += src
endforeach


lwip_srcs += path_srcs