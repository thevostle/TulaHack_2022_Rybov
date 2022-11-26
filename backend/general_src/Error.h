#pragma once

#include "JsonResponse.h"

// TODO: Добавить дебажную инфу в ответ ошибки
struct Error : public JsonResponse
{
    using JsonResponse::JsonResponse;
};