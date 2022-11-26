#pragma once

#include "Error.h"
#include "drogon/HttpTypes.h"

#include <string>
#include <drogon/HttpFilter.h>
#include <chrono>

namespace dr = drogon;
namespace ch = std::chrono;
using namespace std::literals::chrono_literals;

class TimeoutFilter : public dr::HttpFilter<TimeoutFilter>
{
public:
    TimeoutFilter() : HttpFilter() {}
    TimeoutFilter(const TimeoutFilter&)            = default;
    TimeoutFilter(TimeoutFilter&&)                 = default;
    TimeoutFilter& operator=(const TimeoutFilter&) = default;
    TimeoutFilter& operator=(TimeoutFilter&&)      = default;
    ~TimeoutFilter()                               = default;

    void doFilter(const dr::HttpRequestPtr &req, dr::FilterCallback &&decline, 
                    dr::FilterChainCallback &&accept) override
    {
        static ch::milliseconds timeout{1000};
        using TimePoint = ch::steady_clock::time_point;
        
        #define MARK_KEY "timeoutMark"

        auto now = ch::steady_clock::now();
        if (auto session = req->session())
        {
            if (session->find(MARK_KEY))
            {
                if (auto mark = session->get<TimePoint>(MARK_KEY);
                    (now - mark) > timeout)
                {
                    session->modify<TimePoint>(MARK_KEY, [&now](auto &&time){ time = std::move(now); });
                    accept();
                    return;
                }
                else
                {
                    auto msg = "Access interval should be at least " + std::to_string(timeout.count()) + " milliseconds";
                    decline(Error::Response(ErrorCode::TIMEOUT, dr::HttpStatusCode::k429TooManyRequests, std::move(msg)));
                    return;
                }
            }

            session->insert(MARK_KEY, std::move(now));
            accept();
            return;
        }

        decline(Error::Response(ErrorCode::TIMEOUT, dr::HttpStatusCode::k429TooManyRequests, "[CRITICAL] Session not found."));
    }
};