#pragma once

#include "JsonResponse.h"

// TODO: Добавить дебажную инфу в ответ ошибки
// Пока что это тактическая ЗаТыЧкА
struct Error : public JsonResponse
{
    using JsonResponse::JsonResponse;
};