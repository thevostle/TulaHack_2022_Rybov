#pragma once

#include <jsoncpp/json/value.h>
#include <string>
#include <drogon/HttpTypes.h>
#include <drogon/HttpResponse.h>

namespace dr = drogon;

enum ErrorCode
{
    OK = 0,
    UNKNOWN = 1,
    BAD_SESSION = 2,
    TIMEOUT = 3,
    BAD_REQUEST = 4,
    INVALID_PARAMS = 5,
    SQL_ERROR = 6,
};

struct JsonResponse
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
        return dr::HttpResponse::newHttpJsonResponse(std::move(err).toJson());
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

    virtual Json::Value toJson() const
    {
        return _json();
    }

    std::string message;
    dr::HttpStatusCode code;
    ErrorCode rybCode;
};