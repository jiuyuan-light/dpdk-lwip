project('dpdk-tcpip', 'c',
        # Get version number from file.
        # Fallback to "more" for Windows compatibility.
        #version: run_command(find_program('cat', 'more'),
        #    files('VERSION'), check: true).stdout().strip(),
        default_options: [
            'buildtype=release',
            'default_library=static',
            'warning_level=2',
        ]
)

subdir('lwip')
subdir('port')

incdir = include_directories('include', '/usr/include', 'lwip/include', 'port/include')

dpdk = dependency('libdpdk')
allow_experimental_apis = true

executable('dpdk-tcpip', 'main.c', 'dpdk.c', 'link.c', 'lwip.c', lwip_srcs, include_directories : incdir, dependencies: dpdk, c_args : ['-O0', '-g3', '-gdwarf-2', '-Wno-unused-parameter'])