#pragma once

#include "Error.h"

#include <drogon/HttpController.h>
#include <json/value.h>
#include <string>

namespace dr = drogon;
namespace orm = dr::orm;

class ContentController : public dr::HttpController<ContentController>
{
private:
    using Callback = std::function<void (const dr::HttpResponsePtr &)>;
    using Request  = dr::HttpRequestPtr;

    void fetch(const Request &req, Callback &&send)
    {
        auto client = dr::app().getDbClient("user");

        if (!client)
        {
            send(Error::Response(ErrorCode::DB_CLIENT_ERROR, "No client found"));
            return;
        }

        try
        {
            auto result = client->execSqlSync("select * from contents order by rate");

            JsonResponse res{ErrorCode::OK, "Movies fetched"};
            res.add["movies"] = Json::arrayValue;
            auto &movies = res.add["movies"];

            for (auto row : result)
            {
                auto movie = Json::Value{ Json::objectValue };
                movie["id"]         = row["id"]        .as<int>();
                movie["name"]       = row["name"]      .as<std::string>();
                movie["rate"]       = row["rate"]      .as<float>();
                movie["poster_url"] = row["poster_url"].as<std::string>();
                movie["year"]       = row["year"].as<int>();
                movies.append(std::move(movie));
            }

            send(std::move(res).toResponse());
        }
        catch (const orm::DrogonDbException &e)
        {
            send(Error::Response(ErrorCode::SQL_ERROR, "Exception while accesing to database: " + std::string{e.base().what()}));
        }
        
    }
public:
    ContentController() : HttpController() {}

    ContentController(const ContentController&)            = default;
    ContentController(ContentController&&)                 = default;
    ContentController& operator=(const ContentController&) = default;
    ContentController& operator=(ContentController&&)      = default;
    ~ContentController()                                   = default;

    METHOD_LIST_BEGIN

    ADD_METHOD_TO(ContentController::fetch, "/content/fetch", dr::Post, dr::Options,
                  "TimeoutFilter");

    METHOD_LIST_END
};