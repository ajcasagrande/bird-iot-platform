#pragma once

static const char MQTT_CA_CERTIFICATE[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
TODO_PUT_YOUR_CERT_INFO_HERE
-----END CERTIFICATE-----
-----BEGIN CERTIFICATE-----
TODO_PUT_YOUR_CERT_INFO_HERE
-----END CERTIFICATE-----
)EOF";


// Note: this is the root ca.crt for OTA, and not the individual server certs
static const char OTA_CA_CERTIFICATE[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
TODO_PUT_YOUR_CERT_INFO_HERE
-----END CERTIFICATE-----
)EOF";
