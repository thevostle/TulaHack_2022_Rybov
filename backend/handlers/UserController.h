#pragma once

#include "Error.h"
#include "drogon/HttpTypes.h"
#include "drogon/utils/FunctionTraits.h"

#include <drogon/HttpSimpleController.h>
#include <drogon/HttpController.h>
#include <string>

namespace dr = drogon;
namespace orm = dr::orm;

class UserController : public dr::HttpController<UserController>
{
private:
    using Callback = std::function<void (const dr::HttpResponsePtr &)>;
    using Request  = dr::HttpRequestPtr;

    void accept(const Request &req, Callback &&send)
    {
        send(JsonResponse::Response(ErrorCode::BAD_REQUEST, "DEPRECATED"));
    }

    void registerUser(const Request &req, Callback &&send)
    {
        static std::string salt {SALT};

        const auto &params   = req->getParameters();
        const auto &login    = params.at("login");
        const auto &password = params.at("password");

        auto client = dr::app().getDbClient("user");

        if (!client)
        {
            send(Error::Response(ErrorCode::DB_CLIENT_ERROR, "No client found"));
            return;
        }

        try
        {
            auto auth_token  = std::hash<std::string>{}(login + salt + password);
            auto pwdHash     = std::hash<std::string>{}(password + salt);
            (void)client->execSqlSync("insert into users values (NULL, $0, $1, FALSE);",
                                      login, std::move(pwdHash));//, std::move(auth_token));
            auto result = client->execSqlSync("select * from users where login=?1;", login);

            if (auto session = req->session())
            {
                session->insert("auth_token", auth_token);
            }

            JsonResponse res{ErrorCode::OK, "Returned registered user"};
            res.add["id"] = std::to_string(result[0]["id"].as<size_t>());
            res.add["login"] = login;
            send(std::move(res).toResponse());
        }
        catch (const orm::DrogonDbException &e)
        {
            send(Error::Response(ErrorCode::SQL_ERROR, "Exception while accesing to database: " + std::string{e.base().what()}));
        }
    }

    void loginUser(const Request &req, Callback &&send)
    {
        namespace orm = dr::orm;

        static std::string salt {"TulaHack2022Accelerator"};

        const auto &params   = req->getParameters();
        const auto &login    = params.at("login");
        const auto &password = params.at("password");

        auto client = dr::app().getDbClient("user");

        if (!client)
        {
            send(Error::Response(ErrorCode::DB_CLIENT_ERROR, "No client found"));
            return;
        }

        try
        {
            auto result = client->execSqlSync("select * from users where login=?1;", login);

            if (result.size() < 1)
            {
                send(Error::Response(ErrorCode::UNREGISTERED_USER, "User not registered"));
                return;
            } 
            else if (result.size() > 1)
            {
                std::string ids{};
                for (auto &row : result)
                {
                    ids += row.at("id").as<std::string>();
                }
                send(Error::Response(ErrorCode::UNKNOWN, "[CRITICAL] Several users with same login: " + ids));
                return;
            }

            auto dbPwdHash = result[0]["password"].as<size_t>();

            if (dbPwdHash == std::hash<std::string>{}(password + salt))
            {
                if (auto session = req->getSession())
                {
                    session->modify<size_t>("auth_token", [](auto &t){ t = 123123; });
                }

                JsonResponse res{ErrorCode::OK, "Authorized"};
                res.add["id"] = std::to_string(result[0]["id"].as<size_t>());
                res.add["login"] = login;
                send(std::move(res).toResponse());
                return;
            }
            send(Error::Response(ErrorCode::WRONG_PASSWORD, "Wrong password or error in hashing occured"));
        }
        catch (const orm::DrogonDbException &e)
        {
            send(Error::Response(ErrorCode::SQL_ERROR, "Exception while accesing to database: " + std::string{e.base().what()}));
        }
    }

    template<typename T>
    void getByField(const Request &req, Callback &&send, std::string field, T &&value)
    {
        auto client = dr::app().getDbClient("user");

        if (!client)
        {
            send(Error::Response(ErrorCode::DB_CLIENT_ERROR, "No client found"));
            return;
        }

        try
        {
            auto result = client->execSqlSync("select * from users where " + field + "=?1;", std::forward<T>(value));

            if (result.empty())
            {
                send(Error::Response(ErrorCode::USER_NOT_FOUND, "User not found"));
                return;
            }

            JsonResponse res{ErrorCode::OK, "Returned registered user with given ID"};
            auto login       = result[0]["login"].template as<std::string>();
            res.add["id"]    = result[0]["id"].template as<int>();
            res.add["login"] = login;
            send(std::move(res).toResponse());
        }
        catch (const orm::DrogonDbException &e)
        {
            send(Error::Response(ErrorCode::SQL_ERROR, "Exception while accesing to database: " + std::string{e.base().what()}));
        }
    }

    void getById(const Request &req, Callback &&send, size_t id)
    {
        getByField(req, std::move(send), "id", id);
    }

    void getByName(const Request &req, Callback &&send, std::string name)
    {
        getByField(req, std::move(send), "login", std::move(name));
    }
    
public:
    UserController()                                 = default;
    UserController(const UserController&)            = default;
    UserController(UserController&&)                 = default;
    UserController& operator=(const UserController&) = default;
    UserController& operator=(UserController&&)      = default;
    ~UserController()                                = default;

    METHOD_LIST_BEGIN

    ADD_METHOD_TO(UserController::accept, "/user/is_auth", dr::Post, dr::Options,
                  "TimeoutFilter", "CheckLoginFilter");

    ADD_METHOD_TO(UserController::registerUser, "/user/register", dr::Post, dr::Options,
                  "TimeoutFilter", "CheckLoginVars");

    ADD_METHOD_TO(UserController::loginUser, "/user/login", dr::Post, dr::Options,
                  "TimeoutFilter", "CheckLoginVars");
    
    ADD_METHOD_TO(UserController::getById, "/user/get/by_id?id={1}", dr::Post, dr::Options,
                  "TimeoutFilter");

    ADD_METHOD_TO(UserController::getByName, "/user/get/by_name?name={1}", dr::Post, dr::Options,
                  "TimeoutFilter");

    METHOD_LIST_END
};