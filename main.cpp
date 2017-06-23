#include <memory>
#include <iostream>
#include <evhttp.h>
#include "JsonFormer.h"

int main()
{
    if (!event_init())
    {
        std::cerr << "Failed to init libevent" << std::endl;
        return EXIT_FAILURE;
    }

    char const SrvAddress[] = "127.0.0.1";
    std::uint16_t SrvPort = 8080;
    std::unique_ptr<evhttp, decltype(&evhttp_free)> Server(evhttp_start(SrvAddress, SrvPort), &evhttp_free);

    if (!Server)
    {
        std::cerr << "Failed to init http server." << std::endl;
        return EXIT_FAILURE;
    }

    void (*handler)(evhttp_request *req, void *) = [] (evhttp_request *req, void *)
    {
        auto *OutBuf = evhttp_request_get_output_buffer(req);
        if (!OutBuf){
            evhttp_send_reply(req, HTTP_BADREQUEST, "", OutBuf);
            return;
        }

        ReqProcessor request(req);
        JsonFormer jsonFormer;
        evbuffer_add_printf(OutBuf, "%s",jsonFormer.formJsonStr(request).c_str());
        if (jsonFormer.output.compare("404") != 0 || request.type == REQ_BAD) evhttp_send_reply(req, HTTP_NOTFOUND, "", OutBuf);
        else evhttp_send_reply(req, HTTP_OK, "", OutBuf);
    };

    evhttp_set_gencb(Server.get(), handler, nullptr);
    if (event_dispatch() == -1)
    {
        std::cerr << "Failed to run loop" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}