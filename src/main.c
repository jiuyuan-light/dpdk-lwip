#include <stdio.h>

#include "dpdk.h"
#include "lwip.h"

/* TODO */
int config_parse(int argc, char **argv)
{
    return 0;
}

int main(int argc, char **argv)
{
    printf("Hello, dpdk-lwip\n");

    if (config_parse(argc, argv) < 0) {
        return -1;
    }

    if (dpdk_init(argc, argv) < 0) {
        return -1;
    }

    if (lwip_init_on_dpdk(argc, argv) < 0) {
        return -1;
    }

    /* should not be implemented here */
    perror("should not be implemented here\n");
    for (;;);

    return 0;
}