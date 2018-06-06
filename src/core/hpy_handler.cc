#ifndef HPY_CORE_HPY_HANDLER_
#include "core/hpy_handler.h"
#endif

Handler::Handler(ThreadsafeQueue<Tcp>& proxy_tcp_queue)\
        :proxy_tcp_queue_(proxy_tcp_queue)
{

}

bool Handler::RunHandlerService()
{
    

}

bool Handler::HandlerService()
{

}