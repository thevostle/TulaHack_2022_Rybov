#pragma once

#include <drogon/HttpFilter.h>
#include <chrono>

namespace dr = drogon;
namespace ch = std::chrono;
using namespace std::literals::chrono_literals;

class TimeoutFilter : public dr::HttpFilter<TimeoutFilter>
{
private:
    static ch::milliseconds timeout;

public:
    TimeoutFilter() {}

    void doFilter(const dr::HttpRequestPtr &req, dr::FilterCallback &&decline, 
                    dr::FilterChainCallback &&accept) override;
};