#!/usr/bin/env bash

runs=10
begin_ns=$(( $(date +%s%N) ))

for _ in $(seq 1 $runs); do
  idf_size.py /tmp/firmware.map > /dev/null
done

total_ns=$(( $(date +%s%N) - begin_ns ))

printf "%12d nanos (approx. %4d avg millis per run)\n" ${total_ns} $((total_ns / 1000 / 1000 / runs))

