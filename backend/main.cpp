#include <drogon/HttpAppFramework.h>

#include "TimeoutFilter.h"
#include "CheckLoginFilter.h"

#include "RedirectController.h"
#include "LoginController.h"

namespace dr = drogon;

int main()
{
    auto &&app = dr::app();

    app.loadConfigFile("drogonCfg.json")
       .enableSession(60)
       .run();

    return 0;
}