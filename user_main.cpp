#include "user_service/user_http_web_server.h"

int main(int argc, char*argv[]) 
{
    UserHTTPWebServer app;
    return app.run(argc, argv);
}