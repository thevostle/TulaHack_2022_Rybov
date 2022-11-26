#pragma once

#include "Error.h"

#include <drogon/HttpFilter.h>

namespace dr = drogon;

class CheckLoginVars : public dr::HttpFilter<CheckLoginVars>
{
public:
    CheckLoginVars() : HttpFilter() {}
    CheckLoginVars(const CheckLoginVars&)            = default;
    CheckLoginVars(CheckLoginVars&&)                 = default;
    CheckLoginVars& operator=(const CheckLoginVars&) = default;
    CheckLoginVars& operator=(CheckLoginVars&&)      = default;
    ~CheckLoginVars()                                = default;

    void doFilter(const dr::HttpRequestPtr &req, dr::FilterCallback &&decline, 
                  dr::FilterChainCallback &&accept) override
    {
        static int loginMinSize    = 6;
        static int passwordMinSize = 6;

        const auto &params = req->getParameters();

        if (params.empty() || !(params.contains("login") && params.contains("password")))
        {
            decline(Error::Response(ErrorCode::BAD_REQUEST, dr::HttpStatusCode::k400BadRequest,
                                    "Login and password are missing"));
            return;
        }

        const auto &login    = params.at("login");
        const auto &password = params.at("password");

        if (   login.empty() || password.empty() 
            || login.size() < loginMinSize || password.size() < passwordMinSize)
        {
            decline(Error::Response(ErrorCode::INVALID_PARAMS, dr::HttpStatusCode::k400BadRequest,
                                    "Login and password are invalid"));
            return;
        }

        accept();
    }
};