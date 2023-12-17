
#include <optional>
#include "web_server/http_web_server.h"
//#include "other_server/http_other_server.h"

int main(int argc, char*argv[]) 
{
    HTTPOtherWebServer app;
    return app.run(argc, argv);
}