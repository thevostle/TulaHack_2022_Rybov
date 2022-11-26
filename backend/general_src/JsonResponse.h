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
        json["rybCode"]    = rybCode;
        json["additional"] = Json::objectValue;
        return json;
    }

    Json::Value _json() && 
    {
        Json::Value json{};
        json["message"]    = std::move(message);
        json["rybCode"]    = rybCode;
        json["additional"] = Json::objectValue;
        return json;
    }

public:
    static dr::HttpResponsePtr Response(ErrorCode rybCode, std::string msg)
    {
        JsonResponse err{rybCode, std::move(msg)};
        auto response = dr::HttpResponse::newHttpJsonResponse(std::move(err).toJson());
        response->setStatusCode(dr::HttpStatusCode::k200OK);
        response->addHeader("Access-Control-Allow-Origin", "*");
        response->addHeader("Access-Control-Allow-Headers", "*");
        return response;
    }

    JsonResponse()
        : message{}, rybCode(ErrorCode::OK) {}

    JsonResponse(ErrorCode _rybCode, std::string _message)
        : message{std::move(_message)}, rybCode(_rybCode) {}

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
    ErrorCode rybCode;
};