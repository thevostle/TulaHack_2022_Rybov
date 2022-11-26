#pragma once

#include "Error.h"

#include <drogon/HttpAppFramework.h>
#include <drogon/HttpFilter.h>
#include <drogon/orm/DbClient.h>
#include <string>

namespace dr = drogon;

class CheckLoginFilter : public dr::HttpFilter<CheckLoginFilter>
{
public:
    CheckLoginFilter() : HttpFilter() {}
    CheckLoginFilter(const CheckLoginFilter&)            = default;
    CheckLoginFilter(CheckLoginFilter&&)                 = default;
    CheckLoginFilter& operator=(const CheckLoginFilter&) = default;
    CheckLoginFilter& operator=(CheckLoginFilter&&)      = default;
    ~CheckLoginFilter()                                  = default;

    void doFilter(const dr::HttpRequestPtr &req, dr::FilterCallback &&decline, 
                  dr::FilterChainCallback &&accept) override
    {
        static std::string salt {"TulaHack2022Accelerator"};

        if (auto &session = req->getSession())
        {
            if (session->find("auth_token"))
            {
                // Тактический костыль, полностью механизм токенов реализовать не успеем
                accept();
            }
        }

        decline(JsonResponse::Response(ErrorCode::UNAUTHORIZED, "Unauthorized"));
    }
};