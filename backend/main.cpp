#include <drogon/HttpAppFramework.h>

namespace dr = drogon;

int main()
{
    auto &&app = dr::app();

    app.loadConfigFile("drogonCfg.json")
       .enableSession(86400)
       .run();

    return 0;
}