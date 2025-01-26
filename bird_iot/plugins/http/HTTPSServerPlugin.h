#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_HTTPS_SERVER_PLUGIN

#include "include/common.h"

#include <HTTPSServer.hpp>
#include <SSLCert.hpp>
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>

class HTTPSServerPlugin : public IotPlugin {
private:
  httpsserver::SSLCert *cert;
  httpsserver::HTTPSServer *secureServer;
  Task<HTTPSServerPlugin> *task;

public:
  HTTPSServerPlugin();

  bool setup() override;
  bool start() override;
  void execute();
};

extern HTTPSServerPlugin WebServer;

#endif
