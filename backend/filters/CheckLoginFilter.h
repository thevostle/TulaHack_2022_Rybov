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
        namespace orm = dr::orm;

        static std::string salt {"ImATeapotInTulaHack2022Accelerator"};

        const auto &params   = req->getParameters();
        const auto &login    = params.at("login");
        const auto &password = params.at("password");

        auto client = dr::app().getDbClient("user");

        if (!client)
        {
            decline(Error::Response(ErrorCode::DB_CLIENT_ERROR, "No client found"));
            return;
        }

        try
        {
            auto result = client->execSqlSync("select * from users where login=?1;", login);

            if (result.size() < 1)
            {
                decline(Error::Response(ErrorCode::UNREGISTERED_USER, "User not registered"));
                return;
            } 
            else if (result.size() > 1)
            {
                std::string ids{};
                for (auto &row : result)
                {
                    ids += row.at("id").as<std::string>();
                }
                decline(Error::Response(ErrorCode::UNKNOWN, "[CRITICAL] Several users with same login: " + ids));
                return;
            }

            auto dbPwdHash = result[0]["password"].as<size_t>();

            if (dbPwdHash == std::hash<std::string>{}(password + salt))
            {
                accept();
            }
            decline(Error::Response(ErrorCode::WRONG_PASSWORD, "Wrong password or error in hashing occured"));
        }
        catch (const orm::DrogonDbException &e)
        {
            decline(Error::Response(ErrorCode::SQL_ERROR, "Exception while accesing to database: " + std::string{e.base().what()}));
        }
    }
};