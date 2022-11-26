#include "RedirectController.h"

void RedirectController::asyncHandleHttpRequest(const Request &req, Callback &&callback)
{
    callback(dr::HttpResponse::newRedirectionResponse("/index.php"));
}