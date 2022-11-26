#include "CommonFilters.h"
#include "Error.h"

int CheckLoginVars::loginMinSize    = 6;
int CheckLoginVars::passwordMinSize = 6;

void CheckLoginVars::doFilter(const dr::HttpRequestPtr &req, dr::FilterCallback &&decline, 
                              dr::FilterChainCallback &&accept)
{
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
}