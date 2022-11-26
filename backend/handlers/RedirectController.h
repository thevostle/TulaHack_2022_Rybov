#pragma once

#include <drogon/HttpSimpleController.h>

namespace dr = drogon;

class AuthRedirectController : public dr::HttpSimpleController<AuthRedirectController>
{
private:
    using Callback = std::function<void (const dr::HttpResponsePtr &)>;
    using Request  = dr::HttpRequestPtr;

public:
    AuthRedirectController() {}

    void asyncHandleHttpRequest(const Request &req, Callback &&callback) override;

    PATH_LIST_BEGIN
    
    //PATH_ADD("/", "TimeoutFilter");

    PATH_LIST_END
};