#pragma once

#include "LoginController.h"
#include "Error.h"

#include <drogon/HttpController.h>
#include <string>

namespace dr = drogon;

class LoginController : public dr::HttpController<LoginController>
{
public:
    using Callback = std::function<void (const dr::HttpResponsePtr &)>;
    using Request  = dr::HttpRequestPtr;

    void registerUser(const Request &req, Callback &&send)
    {
        namespace orm = dr::orm;

        const auto &params = req->getParameters();

        if (params.empty() || !(params.contains("login") && params.contains("password")))
        {
            send(Error::Response(ErrorCode::BAD_REQUEST, dr::HttpStatusCode::k400BadRequest,
                                "Login and password are missing"));
            return;
        }

        const auto &login    = params.at("login");
        const auto &password = params.at("password");

        if (login.empty() || password.empty() || login.size() < 6 || password.size() < 6)
        {
            send(Error::Response(ErrorCode::INVALID_PARAMS, dr::HttpStatusCode::k400BadRequest,
                                "Login and password are invalid"));
            return;
        }

        auto client = dr::app().getDbClient("client");

        try
        {
            (void)client->execSqlSync("insert into users values (NULL, ?1, ?2);", login, std::hash<std::string>{}(password));
        }
        catch (const orm::DrogonDbException &e)
        {
            send(Error::Response(ErrorCode::SQL_ERROR, dr::HttpStatusCode::k500InternalServerError,
                                "Exception while accesing to database: " + std::string{e.base().what()}));
        }
    }

public:
    LoginController() {}

    METHOD_LIST_BEGIN

    ADD_METHOD_TO(LoginController::registerUser, "/user/register", dr::Post, "TimeoutFilter", "CheckLoginFilter");

    METHOD_LIST_END
};