#!/usr/bin/env python3

import os
import glob
import re
import serial.tools.list_ports

from colors import *


# noinspection PyStringFormat
def print_field(val, length, style='', style_condition=True, right_align=False, end='', begin=''):
    print(f'{begin}{style if style_condition else ""} %{"" if right_align else "-"}{length}s {clear}│' % val, end=end)


def print_header(val, length, **kwargs):
    print_field(val, length, f'{cyan}{bold}', **kwargs)


def find_symlink(device):
    for name in glob.glob('/dev/esp32-*'):
        if os.path.islink(name) and os.readlink(name).replace('/dev/', '') == device.replace('/dev/', ''):
            return name.replace('/dev/', '')
    return None


if __name__ == "__main__":
    print('┌────────────────┬────────────────┬──────────────────────────────────────┬────────────────────────────────────────────────────────┐')
    print_header('Port', 14, begin='│')
    print_header('Device', 14)
    print_header('Description', 36)
    print_header('Hardware Info', 54, end='\n')

    for p in sorted(serial.tools.list_ports.comports(), key=lambda x: x.device):
        lnk = find_symlink(p.device)
        # if not lnk:
        #     regex = re.match(r'(esp32-[0-9a-fA-F]+) = \S+ ' + p.serial_number, )
        #     m = regex.match
        #     lnk = subprocess.check_output(["sed", "-nr", f"s/(esp32-[0-9a-fA-F]+) = \\S+ {p.serial_number}/\\1/p", "Makefile"], shell=True)
        print('├────────────────┼────────────────┼──────────────────────────────────────┼────────────────────────────────────────────────────────┤')
        print_field(p.device, 14, bold, begin='│')
        print_field(lnk if lnk else '', 14, bold)
        print_field(p.description, 36)
        print_field(p.hwid, 54, end='\n')

    print('└────────────────┴────────────────┴──────────────────────────────────────┴────────────────────────────────────────────────────────┘')
