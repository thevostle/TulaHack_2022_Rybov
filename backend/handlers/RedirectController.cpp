#include "RedirectController.h"
#include "JsonResponse.h"

void AuthRedirectController::asyncHandleHttpRequest(const Request &req, Callback &&callback)
{
    callback(RedirectResponse::Response("/auth", true));
}