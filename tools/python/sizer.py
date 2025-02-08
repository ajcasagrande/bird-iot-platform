#!/usr/bin/env python3
import os
import sys
import math
import re
import subprocess
import birdjson

from colors import *


class Sizer:
    def __init__(self, env):
        self.env = env
        self.partitions_csv = f'projects/{self.env}/partitions.csv'
        self.elf = f'projects/{self.env}/build/{self.env}.elf'
        self.map = f'projects/{self.env}/build/{self.env}.map'

        self.partitions_regex = re.compile(r'^app([0-9]), *app, *ota_[0-9], *(0x[0-9a-fA-F]+), *(0x[0-9a-fA-F]+),?$')

        self.max_size = 0
        self.code_size = 0
        self.code_percent = 0.0
        self.data_percent = 0.0
        self.max_code_mb = 0.0
        self.code_mb = 0.0
        self.offset = 0
        self.dram_percent = 0
        self.iram_percent = 0
        self.info = None

    def compute_all(self):
        if not os.path.isfile(self.map):
            sout(f'{red}Map file does not exist for environment \'{bold}{self.env}{normal}\'{clear}\n', True)
            exit(1)

        self.get_max_size()
        self.parse_sizes()
        self.calc_percents()

    def get_max_size(self):
        with open(self.partitions_csv) as f:
            while True:
                line = f.readline()
                if line is None:
                    break

                match = self.partitions_regex.match(line)
                if match:
                    self.offset = int(match.group(2), 16)
                    self.max_size = int(match.group(3), 16)
                    break

        self.max_code_mb = self.max_size / 1024.0 / 1024.0

    def calc_percents(self):
        self.code_percent = self.info.total_size * 100.0 / self.max_size
        self.dram_percent = self.info.used_dram_ratio * 100.0
        self.iram_percent = self.info.used_iram_ratio * 100.0

    def parse_sizes(self):
        output = subprocess.check_output(['tools/python/idf_size.py', '--json', self.map])
        self.info = birdjson.loads(output)
        self.code_mb = self.info.total_size / 1024.0 / 1024.0

    def validate(self):
        if self.info.available_dram < 0:
            sout(f'\n{bold}{red}ERROR: DRAM usage is over the limit by {abs(self.info.available_dram)} bytes {nocolor} ({self.info.used_dram} / {self.info.available_dram + self.info.used_dram} bytes){clear}\n', True)
            sys.exit(1)
        if self.info.available_iram < 0:
            sout(f'\n{bold}{red}ERROR: IRAM usage is over the limit by {abs(self.info.available_iram)} bytes {nocolor} ({self.info.used_iram} / {self.info.available_iram + self.info.used_iram} bytes){clear}\n', True)
            sys.exit(1)
        if self.info.total_size > self.max_size:
            sout(f'\n{bold}{red}ERROR: Program too large to fit OTA partition by {self.info.total_size - self.max_size} bytes!{nocolor} ({self.info.total_size} / {self.max_size} bytes){clear}\n', True)
            sys.exit(1)


def sout(val, flush=False):
    sys.stdout.write(val)
    if flush:
        sflush()


def sflush():
    sys.stdout.flush()


def print_percent(value, min=0, max=100, step=2, end=None, color=None):
    sout(color if color is not None else color_by_percent(value))
    for x in range(min+step, max+step, step):
        if x < math.ceil(value):
            sout(u'█')
        else:
            sout(u'░')
    if end is not None:
        sout(end)
    sout(clear, True)


def color_by_percent(percent):
    if percent > 90.0:
        return red
    elif percent > 80.0:
        return yellow
    else:
        return cyan


def main(env):
    s = Sizer(env)
    s.compute_all()

    sout(f'\n   {bold}DRAM {normal}')
    print_percent(s.dram_percent)
    sout(f' {bold}{s.dram_percent:.1f}%{normal} ( {bold}{s.info.used_dram / 1024.0:5.1f}{normal} KB / {bold}{(s.info.used_dram + s.info.available_dram) / 1024.0:5.1f}{normal} KB )\n')

    sout(f'\n   {bold}IRAM {normal}')
    print_percent(s.iram_percent)
    sout(f' {bold}{s.iram_percent:.1f}%{normal} ( {bold}{s.info.used_iram/1024.0:5.1f}{normal} KB / {bold}{(s.info.used_iram + s.info.available_iram)/1024.0:5.1f}{normal} KB )\n')

    sout(f'\n{bold}Program {normal}')
    print_percent(s.code_percent)
    sout(f' {bold}{s.code_percent:.1f}%{normal} ( {bold}{s.code_mb:5.2f}{normal} MB / {bold}{s.max_code_mb:5.2f}{normal} MB )\n')
    print()

    s.validate()


if __name__ == '__main__':
    import plac
    plac.call(main)



# Total sizes:
# DRAM .data size:   14132 bytes
# DRAM .bss  size:   35128 bytes
# Used static DRAM:  49260 bytes (  75320 available, 39.5% used)
# Used static IRAM: 108605 bytes (  22467 available, 82.9% used)
# Flash code:  923103 bytes
# Flash rodata:  300984 bytes
# Total image size:~1346824 bytes (.bin may be padded larger)

# Retrieving maximum program size .pio\build\pcb_oled_sh1106\firmware.elf
# Checking size .pio\build\pcb_oled_sh1106\firmware.elf
# Memory Usage -> http://bit.ly/pio-memory-usage
# DATA:    [==        ]  16.1% (used 52872 bytes from 327680 bytes)
# PROGRAM: [========= ]  93.1% (used 1525038 bytes from 1638400 bytes)
# esptool.py v2.6
