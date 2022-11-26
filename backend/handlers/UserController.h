#pragma once

#include "Error.h"
#include "drogon/HttpTypes.h"
#include "drogon/utils/FunctionTraits.h"

#include <drogon/HttpSimpleController.h>
#include <drogon/HttpController.h>
#include <string>

namespace dr = drogon;

class UserController : public dr::HttpController<UserController>
{
private:
    using Callback = std::function<void (const dr::HttpResponsePtr &)>;
    using Request  = dr::HttpRequestPtr;
    using dr::HttpController<UserController>::HttpController;

    void acceptRequest(const Request &req, Callback &&send)
    {
        send(JsonResponse::Response(ErrorCode::AUTORIZED, "Authorized"));
    }

    void registerUser(const Request &req, Callback &&send)
    {
        namespace orm = dr::orm;

        static std::string salt {"ImATeapotInTulaHack2022Accelerator"};

        const auto &params = req->getParameters();
        const auto &login    = params.at("login");
        const auto &password = params.at("password");

        auto client = dr::app().getDbClient("user");

        if (!client)
        {
            send(Error::Response(ErrorCode::DB_CLIENT_ERROR, "No client found"));
        }

        try
        {
            auto result = client->execSqlSync("insert into users values (NULL, $0, $1);", login, std::hash<std::string>{}(password + salt));
            send(JsonResponse::Response(ErrorCode::OK, "User registered"));
        }
        catch (const orm::DrogonDbException &e)
        {
            send(Error::Response(ErrorCode::SQL_ERROR, "Exception while accesing to database: " + std::string{e.base().what()}));
        }
    }
    
public:
    UserController()                                 = default;
    UserController(const UserController&)            = default;
    UserController(UserController&&)                 = default;
    UserController& operator=(const UserController&) = default;
    UserController& operator=(UserController&&)      = default;
    ~UserController()                                = default;

    METHOD_LIST_BEGIN

    ADD_METHOD_TO(UserController::registerUser, "/user/register", dr::Post, dr::Options,
                  "TimeoutFilter", "CheckLoginVars");

    ADD_METHOD_TO(UserController::acceptRequest, "/user/login", dr::Post, dr::Options,
                  "TimeoutFilter", "CheckLoginVars", "CheckLoginFilter");

    METHOD_LIST_END
};