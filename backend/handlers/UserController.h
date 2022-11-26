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
        send(JsonResponse::Response(ErrorCode::AUTORIZED, dr::HttpStatusCode::k200OK, "Authorized"));
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
            send(Error::Response(ErrorCode::DB_CLIENT_ERROR, dr::HttpStatusCode::k500InternalServerError,
                                    "No client found"));
        }

        try
        {
            auto result = client->execSqlSync("insert into users values (NULL, ?1, ?2);", login, std::hash<std::string>{}(password + salt));

            if (result.affectedRows() != 1)
            {
                send(Error::Response(ErrorCode::SQL_ERROR, dr::HttpStatusCode::k500InternalServerError,
                                     "No rows were inserted"));
            }

            send(JsonResponse::Response(ErrorCode::OK, dr::HttpStatusCode::k200OK, "User registered"));
        }
        catch (const orm::DrogonDbException &e)
        {
            send(Error::Response(ErrorCode::SQL_ERROR, dr::HttpStatusCode::k500InternalServerError,
                                    "Exception while accesing to database: " + std::string{e.base().what()}));
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

    ADD_METHOD_TO(UserController::registerUser, "/user/register", dr::Post,
                  "TimeoutFilter", "CheckLoginVars");

    ADD_METHOD_TO(UserController::acceptRequest, "/user/login", dr::Post,
                  "TimeoutFilter", "CheckLoginVars", "CheckLoginFilter");

    METHOD_LIST_END
};