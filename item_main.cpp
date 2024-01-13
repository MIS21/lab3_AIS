
#include <optional>
#include "item_service/http_item_web_server.h"
//#include "other_server/http_other_server.h"

int main(int argc, char*argv[]) 
{
    ItemHTTPWebServer app;
    return app.run(argc, argv);
}