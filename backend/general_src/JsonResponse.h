#pragma once

#include "drogon/utils/FunctionTraits.h"
#include <jsoncpp/json/value.h>
#include <string>
#include <drogon/HttpTypes.h>
#include <drogon/HttpResponse.h>

#define SALT "TulaHack2022Accelerator"

namespace dr = drogon;

enum ErrorCode
{
    OK = 0,
    UNKNOWN = 1,
    TIMEOUT = 3,

    BAD_SESSION = 2,
    BAD_REQUEST = 4,
    INVALID_PARAMS = 5,
    UNAUTHORIZED = 11,

    SQL_ERROR = 6,
    DB_CLIENT_ERROR = 7,
    UNREGISTERED_USER = 8,
    WRONG_PASSWORD = 9,
    USER_NOT_FOUND = 10,
};

struct BaseResponse
{
    virtual dr::HttpResponsePtr toResponse() const & = 0;
    virtual dr::HttpResponsePtr toResponse() && = 0;
};

struct JsonResponse : public BaseResponse
{
    static dr::HttpResponsePtr Response(ErrorCode rybCode, std::string msg, Json::Value add = Json::objectValue)
    {
        JsonResponse res{ rybCode, std::move(msg), std::move(add) };
        return res.toResponse();
    }

    JsonResponse()
        : message{}, rybCode(ErrorCode::OK), add{Json::objectValue} {}

    JsonResponse(ErrorCode _rybCode, std::string _message, Json::Value _add = {})
        : message{std::move(_message)}, rybCode(_rybCode), add(std::move(_add)) {}

    JsonResponse(const JsonResponse&)            = default;
    JsonResponse(JsonResponse&&)                 = default;
    JsonResponse& operator=(const JsonResponse&) = default;
    JsonResponse& operator=(JsonResponse&&)      = default;
    ~JsonResponse()                              = default;

    virtual Json::Value toJson() const &
    {
        Json::Value json{};
        json["message"]    = message;
        json["rybCode"]    = rybCode;
        json["additional"] = add;
        return json;
    }

    virtual Json::Value toJson() &&
    {
        Json::Value json{};
        json["message"]    = std::move(message);
        json["rybCode"]    = rybCode;
        json["additional"] = std::move(add);
        return json;
    }

    dr::HttpResponsePtr toResponse() const & override
    {
        auto response = dr::HttpResponse::newHttpJsonResponse(toJson());
        response->setStatusCode(dr::HttpStatusCode::k200OK);
        response->addHeader("Access-Control-Allow-Origin", "*");
        response->addHeader("Access-Control-Allow-Headers", "*");
        return response;
    }

    dr::HttpResponsePtr toResponse() && override
    {
        auto response = dr::HttpResponse::newHttpJsonResponse(toJson());
        response->setStatusCode(dr::HttpStatusCode::k200OK);
        response->addHeader("Access-Control-Allow-Origin", "*");
        response->addHeader("Access-Control-Allow-Headers", "*");
        return response;
    }

    Json::Value add;
    std::string message;
    ErrorCode rybCode;

};

namespace tags
{
    struct FullUrlTag{};
}

struct RedirectResponse : public BaseResponse
{
public:
    static dr::HttpResponsePtr Response(const std::string &url, bool redirectToFrontend = false)
    {
        static std::string frontUrl{ "https://c20e-94-28-235-94.eu.ngrok.io" };
        static std::string backUrl { "https://0e44-94-28-235-94.eu.ngrok.io" };
        return dr::HttpResponse::newRedirectionResponse((redirectToFrontend ? frontUrl : backUrl) + url);
    }

    static dr::HttpResponsePtr Response(std::string url, tags::FullUrlTag)
    {
        return dr::HttpResponse::newRedirectionResponse(std::move(url));
    }

    RedirectResponse(std::string_view _url)
        : url(_url) {}

    RedirectResponse(const RedirectResponse&)            = default;
    RedirectResponse(RedirectResponse&&)                 = default;
    RedirectResponse& operator=(const RedirectResponse&) = default;
    RedirectResponse& operator=(RedirectResponse&&)      = default;
    ~RedirectResponse()                                  = default;

    dr::HttpResponsePtr toResponse() const & override
    {
        return dr::HttpResponse::newHttpJsonResponse(url);
    }

    dr::HttpResponsePtr toResponse() && override
    {
        return dr::HttpResponse::newHttpJsonResponse(std::move(url));
    }

private:
    std::string url;
};