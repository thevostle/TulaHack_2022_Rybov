#pragma once

#include <drogon/HttpSimpleController.h>

#include "Error.h"

namespace dr = drogon;

class RedirectController : public dr::HttpSimpleController<RedirectController>
{
private:
    using Callback = std::function<void (const dr::HttpResponsePtr &)>;
    using Request  = dr::HttpRequestPtr;

public:
    RedirectController() {}

    void asyncHandleHttpRequest(const Request &req, Callback &&callback) override;

    PATH_LIST_BEGIN

    //PATH_ADD("/");

    PATH_LIST_END
};