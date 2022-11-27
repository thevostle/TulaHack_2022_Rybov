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
                auto movieId        = row["id"]        .as<int>();
                movie["id"]         = movieId;
                movie["name"]       = row["name"]      .as<std::string>();
                movie["rate"]       = row["rate"]      .as<float>();
                movie["poster_url"] = row["poster_url"].as<std::string>();
                movie["year"]       = row["year"]      .as<int>();

                auto genresSelect = client->execSqlSync("select * from contentGenges where contend_id=?1", movieId);
                auto &genres = (movie["genresIds"] = Json::arrayValue);

                int i = 0; // size_t is ambigous (Jsoncpp issue)
                for (auto it = genresSelect.begin(); it != genresSelect.end(); ++it, ++i)
                {
                    genres[i] = (*it)["genreId"].as<int>();
                }

                movies.append(std::move(movie));
            }

            send(std::move(res).toResponse());
        }
        catch (const orm::DrogonDbException &e)
        {
            send(Error::Response(ErrorCode::SQL_ERROR, "Exception while accesing to database: " + std::string{e.base().what()}));
        }
    }

    void get(const Request &req, Callback &&send, size_t id)
    {
        auto client = dr::app().getDbClient("user");

        if (!client)
        {
            send(Error::Response(ErrorCode::DB_CLIENT_ERROR, "No client found"));
            return;
        }

        try
        {
            auto result = client->execSqlSync("select * from contents where id=?1", id);
            JsonResponse res{ErrorCode::OK, "Movie fetched"};

            auto row = result[0];
            res.add["name"]       = row["name"]      .as<std::string>();
            res.add["rate"]       = row["rate"]      .as<float>();
            res.add["poster_url"] = row["poster_url"].as<std::string>();
            res.add["year"]       = row["year"]      .as<int>();

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

    ADD_METHOD_TO(ContentController::get, "/content/get?id={1}", dr::Post, dr::Options,
                  "TimeoutFilter");

    METHOD_LIST_END
};