#!/usr/bin/env bash

IDF_VER=${IDF_VER:-v4.0.2}

TTYS=
ports=$(ls /dev/serial/by-id/* 2>/dev/null || true)

for x in $ports; do
  echo "Device: $x"
  TTYS="${TTYS} --device $x:$x"
done

mkdir -p ./.ccache
chown "$(id -u):$(id -u)" ./.ccache

docker run -it --rm \
  --net=host \
  -v .:/opt/projects/bird-iot \
  -v "./.ccache://.ccache" \
  -v "/dev:/dev" \
  -w /opt/projects/bird-iot \
  -u "$(id -u):$(id -u)" \
  ${TTYS} \
  "ajcasagrande/bird-iot:esp-idf-${IDF_VER}" \
  make DOCKER_BUILD=true "$@"
