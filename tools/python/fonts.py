#!/usr/bin/env python3

import requests
import birdjson
import os

from colors import *

url = 'http://oleddisplay.squix.ch/rest/fontArray'
base_folder = '/opt/projects/bird-iot/bird_iot/include/fonts'
families = [
  # 'Roboto',
  'Roboto Condensed',
  # 'Orbitron',
  # 'DejaVu Sans',
  # 'DejaVu Sans Mono',
  # 'DialogInput',
  # 'Permanent Marker',
  # 'Roboto Mono',
  # 'Meteocons',
  # 'Open Sans Condensed',
  # 'Open Sans Condensed Light',
  # 'Walter Turncoat',
  # 'DSEG7 Classic Mini',
  # '',
  # '',
  # '',
  # '',
]
styles = {'': '0', 'Bold': '1'}
begin_size = 84
end_size = 96
size_step = 2
sizes = range(begin_size, end_size + size_step, size_step)
# sizes = [76, 80, 82, 90, 92, 96]
lib_version = 'gfx'


def download_font(family, style_name, style_value, size):
  _family = family.replace(' ', '_')
  name = f'{_family}_{style_name}_{size}'.replace('__', '_')
  family_path = f'{base_folder}/{_family.lower()}'
  os.makedirs(family_path, exist_ok=True)
  fullname = f'{family_path}/{name}.h'
  include_name = f'{_family.lower()}/{name}.h'
  include_file = f'{family_path}.h'

  if os.path.isfile(fullname):
    print(f'{dim}Skipping:', fullname.replace(base_folder + '/', ''), clear)
    return

  print(f'{magenta}Downloading: ', fullname.replace(base_folder + '/', ''), '...', clear, sep='')

  payload = {'fontArray': '', 'libVersion': lib_version, 'name': family, 'size': size, 'style': style_value}
  r = requests.post(url, json=payload)
  js = birdjson.loads(r.text)

  if 'fontArray' not in js:
    print(red, r.text, clear, sep='')
    return

  if js.name != family:
    print(yellow, f'Got {js.name}, expected {family}', clear, sep='')
  if js.style != style_value:
    print(yellow, f'Got {js.style}, expected {style_value}', clear, sep='')

  data = js.fontArray

  write_font(fullname, include_file, include_name, data)


def write_font(fullname, include_file, include_name, data):
  with open(fullname, 'w') as f:
    f.write('#pragma once\n\n')
    f.write(data)
    f.write('\n')

  if not os.path.isfile(include_file):
    with open(include_file, 'a') as f:
      f.write('#pragma once\n\n')

  with open(include_file, 'a') as f:
    f.write(f'#include "{include_name}"\n')


if __name__ == "__main__":
  for fam in families:
    if fam == '':
      continue
    for k, v in styles.items():
      for sz in sizes:
        download_font(fam, k, v, sz)
