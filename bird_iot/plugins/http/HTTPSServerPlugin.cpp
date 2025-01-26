#include "HTTPSServerPlugin.h"
#if CONFIG_ENABLE_HTTPS_SERVER_PLUGIN

using namespace httpsserver;

// Declare some handler functions for the various URLs on the server
void handleRoot(HTTPRequest * req, HTTPResponse * res);
void handle404(HTTPRequest * req, HTTPResponse * res);

HTTPSServerPlugin WebServer;

static void _execute(HTTPSServerPlugin *plugin) {
  plugin->execute();
}

HTTPSServerPlugin::HTTPSServerPlugin() : IotPlugin("HTTPS Server Plugin") {
  task = new Task<HTTPSServerPlugin>("HTTPS Server", this, _execute);
}

bool HTTPSServerPlugin::setup() {
  cert = new SSLCert();

  int createCertResult = createSelfSignedCert(
      *cert,
      KEYSIZE_2048,
      (String("CN=") + deviceId() + ",O=BirdIoT,C=US").c_str());

  if (createCertResult != 0) {
    LOGE(TAG, "Error generating certificate");
    return false;
  }

  LOGI(TAG, "Certificate created with success");

  secureServer = new HTTPSServer(cert);

  // Create nodes
  auto *nodeRoot = new ResourceNode("/", "GET", &handleRoot);
  auto *node404 = new ResourceNode("", "GET", &handle404);

  // Add nodes to the server
  secureServer->registerNode(nodeRoot);
  secureServer->setDefaultNode(node404);

  return task->configure(3, _6k, MEDIUM_PRIORITY);
}

void HTTPSServerPlugin::start() {
  secureServer->start();
  return task->start();
}

void HTTPSServerPlugin::execute() {
  secureServer->loop();
}

void handleRoot(HTTPRequest * req, HTTPResponse * res) {
  // Status code is 200 OK by default.
  // We want to deliver a simple HTML page, so we send a corresponding content type:
  res->setHeader("Content-Type", "text/html");

  // The response implements the Print interface, so you can use it just like
  // you would write to Serial etc.
  res->println("<!DOCTYPE html>");
  res->println("<html>");
  res->println("<head><title>Hello World!</title></head>");
  res->println("<body>");
  res->println("<h1>Hello World!</h1>");
  res->print("<p>Your server is running for ");
  // A bit of dynamic data: Show the uptime
  res->print((int)(millis()/1000), DEC);
  res->println(" seconds.</p>");
  res->println("</body>");
  res->println("</html>");
}

void handle404(HTTPRequest * req, HTTPResponse * res) {
  // Discard request body, if we received any
  // We do this, as this is the default node and may also server POST/PUT requests
  req->discardRequestBody();

  // Set the response status
  res->setStatusCode(404);
  res->setStatusText("Not Found");

  // Set content type of the response
  res->setHeader("Content-Type", "text/html");

  // Write a tiny HTTP page
  res->println("<!DOCTYPE html>");
  res->println("<html>");
  res->println("<head><title>Not Found</title></head>");
  res->println("<body><h1>404 Not Found</h1><p>The requested resource was not found on this server.</p></body>");
  res->println("</html>");
}

#endif // CONFIG_ENABLE_HTTPS_SERVER_PLUGIN
