#pragma once

#include "Error.h"

#include <drogon/HttpController.h>
#include <json/value.h>
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

    void addRate(const Request &req, Callback &&send, size_t userId, size_t movieId, float rate)
    {
        auto client = dr::app().getDbClient("user");

        if (!client)
        {
            send(Error::Response(ErrorCode::DB_CLIENT_ERROR, "No client found"));
            return;
        }

        try
        {
            if (auto select = client->execSqlSync("select * from userRates where userId=?1 and contentId=?2", userId, movieId);
                !select.empty())
            {
                send(Error::Response(ErrorCode::NO_MODIFY, "User already rated this movie. Use update request from API"));
                return;
            }

            auto genres = client->execSqlSync("select * from contentGenges where contend_id=?1", movieId);

            for (int i = 0; i < genres.size(); ++i)
            {
                auto genreId = genres[i]["genreId"].as<int>();

                if (auto check = client->execSqlSync("select * from userWeights where userId=?1 and genreId=?2", userId, genreId);
                    check.empty())
                {
                    (void)client->execSqlSync("insert into userWeights values(NULL, ?1, ?2, 0)", userId, genreId);
                }

                (void)client->execSqlSync("update userWeights set `weight`=`weight` + ?1 where userId=?2 and genreId=?3", rate, userId, genreId);
            }

            auto result = client->execSqlSync("insert into userRates values (NULL, ?1, ?2, ?3)", userId, movieId, rate);
            send(JsonResponse::Response(ErrorCode::OK, "User rate added"));
        }
        catch (const orm::DrogonDbException &e)
        {
            send(Error::Response(ErrorCode::SQL_ERROR, "Exception while accesing to database: " + std::string{e.base().what()}));
        }
        
    }

    void updateRate(const Request &req, Callback &&send, size_t userId, size_t movieId, float rate)
    {
        auto client = dr::app().getDbClient("user");

        if (!client)
        {
            send(Error::Response(ErrorCode::DB_CLIENT_ERROR, "No client found"));
            return;
        }

        try
        {
            auto result = client->execSqlSync("update userRates set (userId=?1, contentId=?2, rate=?3) where userId=?1 and contentId=?2", userId, movieId, rate);

            if (result.affectedRows() < 1)
            {
                send(Error::Response(ErrorCode::NO_MODIFY, "No user rates were found or updated"));
                return;
            }

            send(JsonResponse::Response(ErrorCode::OK, "User rate updated"));
        }
        catch (const orm::DrogonDbException &e)
        {
            send(Error::Response(ErrorCode::SQL_ERROR, "Exception while accesing to database: " + std::string{e.base().what()}));
        }
        
    }

    void getRecommends(const Request &req, Callback &&send, size_t userId, size_t movieId, float rate)
    {
        
    }

public:
    UserRatesController() : HttpController() {}

    UserRatesController(const UserRatesController&)            = default;
    UserRatesController(UserRatesController&&)                 = default;
    UserRatesController& operator=(const UserRatesController&) = default;
    UserRatesController& operator=(UserRatesController&&)      = default;
    ~UserRatesController()                                     = default;

    METHOD_LIST_BEGIN

    ADD_METHOD_TO(UserRatesController::fetch, "/user/{1}/rates/fetch", dr::Post, dr::Options,
                  "TimeoutFilter");

    ADD_METHOD_TO(UserRatesController::addRate, "/user/{1}/rates/add?movieId={2}&rate={3}", dr::Post, dr::Options,
                  "TimeoutFilter");

    ADD_METHOD_TO(UserRatesController::updateRate, "/user/{1}/rates/update?movieId={2}&rate={3}", dr::Post, dr::Options,
                  "TimeoutFilter");

    ADD_METHOD_TO(UserRatesController::getRecommends, "/user/{1}/recommends/get", dr::Post, dr::Options,
                  "TimeoutFilter");

    METHOD_LIST_END
};