#!/usr/bin/env python3

import time
import socket
import sys
import argparse
import semver

import birdjson
from zeroconf import ServiceBrowser, Zeroconf

from colors import *

SERVICE_TYPES = ['_birdiot', '_arduino']


class ServiceListener:
    services = {}
    args = None

    def __init__(self):
        pass

    @staticmethod
    def update_service(zconf, service_type: str, name: str) -> None:
        pass

    @staticmethod
    def remove_service(zconf, service_type, name):
        host = name.replace('.' + service_type, '')
        js = ServiceListener.services[host]
        print('├────────────────┼──────────────┼────────────────┼────────────┼───────────────┼───────────────────────┤')
        print_field(host, 14, f'{bold}{lt_red}', begin='│')
        print_field(js.ip, 12, dim)
        print_field(js.env, 14, dim)
        print_field('-', 10, dim)
        print_field('-', 13, dim)
        print_field('-', 21, dim, end='\n')

    @staticmethod
    def add_service(zconf, service_type, name):
        info = zconf.get_service_info(service_type, name)
        js = birdjson.JsonObject(server=info.server, name=info.name, ip=socket.inet_ntoa(info.addresses[0]),
                                 **vars(birdjson.loads(str(birdjson.JsonObject(p=info.properties))).p))
        host = info.name.replace('.' + service_type, '')
        ServiceListener.services[host] = js
        if 'env' in js:
            print('├────────────────┼──────────────┼────────────────┼────────────┼───────────────┼───────────────────────┤')
            print_field(host, 14, bold, begin='│')
            print_field(js.ip, 12)
            print_field(js.env, 14)
            ucolor = ''
            vcolor = ''
            if js.update_channel == 'dev':
                ucolor = lt_blue
            elif js.update_channel == 'stable':
                ucolor = f'{bold}'
            print_field(js.update_channel, 10, ucolor)
            cv = ServiceListener.args.current_version
            if cv is not None:
                r = semver.compare(semver.finalize_version(cv), semver.finalize_version(js.version))
                if r == 0:
                    vcolor = f'{bold}{green}' if cv == js.version else f'{green}'
                elif r == 1:
                    vcolor = yellow
            print_field(js.version, 13, vcolor, True)
            print_field(js.revision, 21, lt_red, js.revision.endswith('-dirty'), end='\n')
        else:
            print(birdjson.dumps(js))


# noinspection PyStringFormat
def print_field(val, length, style='', style_condition=True, right_align=False, end='', begin=''):
    print(f'{begin}{style if style_condition else ""} %{"" if right_align else "-"}{length}s {clear}│' % val, end=end)


def print_header(val, length, **kwargs):
    print_field(val, length, f'{cyan}{bold}', **kwargs)


if __name__ == '__main__':
    parser = argparse.ArgumentParser('mDNS Discovery')

    parser.add_argument(
        '--current-version', '-v',
        dest='current_version',
        help='Current Software Version',
        default=None
    )

    ServiceListener.args = parser.parse_args()

    z = Zeroconf()
    listener = ServiceListener()

    print('┌────────────────┬──────────────┬────────────────┬────────────┬───────────────┬───────────────────────┐')
    print_header('Device Id', 14, begin='│')
    print_header('IP Address', 12)
    print_header('Build Env', 14)
    print_header('Channel', 10)
    print_header('Version', 13)
    print_header('Revision', 21, end='\n')

    for s_type in SERVICE_TYPES:
        ServiceBrowser(z, f'{s_type}._tcp.local.', listener)

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        sys.stdout.write('\b\b')
        sys.stdout.flush()
    finally:
        print('└────────────────┴──────────────┴────────────────┴────────────┴───────────────┴───────────────────────┘')
    #    try:
    #        z.close()
    #        print('done')
    #    except KeyboardInterrupt:
    #        print('\nKilled')
