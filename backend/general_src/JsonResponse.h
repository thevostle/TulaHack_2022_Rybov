#pragma once

#include "drogon/utils/FunctionTraits.h"
#include <jsoncpp/json/value.h>
#include <string>
#include <drogon/HttpTypes.h>
#include <drogon/HttpResponse.h>

namespace dr = drogon;

enum ErrorCode
{
    OK = 0,
    UNKNOWN = 1,
    TIMEOUT = 3,

    BAD_SESSION = 2,
    BAD_REQUEST = 4,
    INVALID_PARAMS = 5,

    SQL_ERROR = 6,
    DB_CLIENT_ERROR = 7,
    UNREGISTERED_USER = 8,
    WRONG_PASSWORD = 9,
    AUTORIZED = 10,
};

struct BaseResponse
{
    virtual Json::Value toJson()                const = 0;
    virtual dr::HttpResponsePtr toResponse()    const = 0;
};

struct JsonResponse : public BaseResponse
{
private:
    Json::Value _json() const &
    {
        Json::Value json{};
        json["message"]    = message;
        json["code"]       = code;
        json["rybCode"]    = rybCode;
        json["additional"] = Json::objectValue;
        return json;
    }

    Json::Value _json() && 
    {
        Json::Value json{};
        json["message"]    = std::move(message);
        json["code"]       = code;
        json["rybCode"]    = rybCode;
        json["additional"] = Json::objectValue;
        return json;
    }

public:
    static dr::HttpResponsePtr Response(ErrorCode rybCode, dr::HttpStatusCode code, std::string msg)
    {
        JsonResponse err{rybCode, code, std::move(msg)};
        auto response = dr::HttpResponse::newHttpJsonResponse(std::move(err).toJson());
        response->setStatusCode(code);
        response->addHeader("Referrer-Policy", "unsafe-url");
        return response;
    }

    JsonResponse()
        : message{}, code(dr::HttpStatusCode::k200OK), rybCode(ErrorCode::OK) {}

    JsonResponse(ErrorCode _rybCode, dr::HttpStatusCode _code, std::string _message)
        : message{std::move(_message)}, code(_code), rybCode(_rybCode) {}

    JsonResponse(const JsonResponse&)            = default;
    JsonResponse(JsonResponse&&)                 = default;
    JsonResponse& operator=(const JsonResponse&) = default;
    JsonResponse& operator=(JsonResponse&&)      = default;
    ~JsonResponse()                              = default;

    Json::Value toJson() const override 
    {
        return _json();
    }

    dr::HttpResponsePtr toResponse() const override
    {
        return dr::HttpResponse::newHttpJsonResponse(toJson());
    }

    std::string message;
    dr::HttpStatusCode code;
    ErrorCode rybCode;
};