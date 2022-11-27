#pragma once

#include "Error.h"

#include <drogon/HttpController.h>
#include <string>

namespace dr = drogon;
namespace orm = dr::orm;

class UserRatesController : public dr::HttpController<UserRatesController>
{
private:
    using Callback = std::function<void (const dr::HttpResponsePtr &)>;
    using Request  = dr::HttpRequestPtr;

    void fetch(const Request &req, Callback &&send, size_t userId)
    {
        auto client = dr::app().getDbClient("user");

        if (!client)
        {
            send(Error::Response(ErrorCode::DB_CLIENT_ERROR, "No client found"));
            return;
        }

        try
        {
            auto result = client->execSqlSync("select * from userRates where userId=?1 order by rate", userId);
            
            JsonResponse res{ErrorCode::OK, "User rates fetched"};
            res.add["rates"] = Json::arrayValue;
            auto &rates = res.add["rates"];

            for (auto row : result)
            {
                auto rate          = Json::Value{ Json::objectValue };
                rate["movieId"]    = row["contentId"].as<int>();
                rate["userRate"]   = row["rate"].as<float>();
                rates.append(std::move(rate));
            }

            send(std::move(res).toResponse());
        }
        catch (const orm::DrogonDbException &e)
        {
            send(Error::Response(ErrorCode::SQL_ERROR, "Exception while accesing to database: " + std::string{e.base().what()}));
        }
        
    }

public:
    UserRatesController() : HttpController() {}

    UserRatesController(const UserRatesController&)            = default;
    UserRatesController(UserRatesController&&)                 = default;
    UserRatesController& operator=(const UserRatesController&) = default;
    UserRatesController& operator=(UserRatesController&&)      = default;
    ~UserRatesController()                                 = default;

    METHOD_LIST_BEGIN

    ADD_METHOD_TO(UserRatesController::fetch, "/user/{1}/rates/fetch", dr::Post, dr::Options,
                  "TimeoutFilter");

    METHOD_LIST_END
};