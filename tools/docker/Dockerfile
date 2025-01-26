ARG IDF_VER="v4.0.2"
FROM espressif/idf:${IDF_VER}

COPY python/idf_size.py /opt/esp/idf/tools/idf_size.py

COPY python/requirements.txt /tmp/requirements.txt
RUN /opt/esp/entrypoint.sh pip3 install -r /tmp/requirements.txt

ENV LC_ALL=C.UTF-8

