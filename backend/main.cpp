#include <drogon/HttpAppFramework.h>

#include "CommonFilters.h"
#include "TimeoutFilter.h"
#include "CheckLoginFilter.h"

#include "RatesController.h"
#include "ContentController.h"
#include "UserController.h"
#include "RedirectController.h"

namespace dr = drogon;

int main()
{
    auto &&app = dr::app();

    app.loadConfigFile("drogonCfg.json")
       .enableSession(60)
       .run();

    return 0;
}