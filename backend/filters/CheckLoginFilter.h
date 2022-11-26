#pragma once

#include <drogon/HttpFilter.h>

namespace dr = drogon;

class CheckLoginFilter : public dr::HttpFilter<CheckLoginFilter>
{
public:
    CheckLoginFilter() {}
    
    void doFilter(const dr::HttpRequestPtr &req, dr::FilterCallback &&decline, 
                  dr::FilterChainCallback &&accept) override
    {
        // Нереальная тактическая затычка
        accept();
    }
};