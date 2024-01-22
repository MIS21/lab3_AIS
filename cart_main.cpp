
#include <optional>
#include "cart_service/http_cart_web_server.h"

int main(int argc, char*argv[]) 
{
    CartHTTPWebServer app;
    return app.run(argc, argv);
}