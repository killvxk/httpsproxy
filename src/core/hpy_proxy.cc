#ifndef HPY_CORE_HPY_PROXY_
#include "core/hpy_proxy.h"
#endif

#include <thread>


#ifndef HPY_CORE_HPY_CONST_
#include "core/hpy_const.h"
#endif

Proxy::Proxy():kTcpQueueCapacity_(hpy::Proxy::kTcpQueueDefaultCapacity)
{
    Init();
}

Proxy::Proxy(int tcp_queue_capacity):kTcpQueueCapacity_(tcp_queue_capacity)
{
    Init();
}

bool Proxy::Init()
{
    handler_ = new Handler(proxy_tcp_queue_);
}

bool Proxy::RunProxyService()
{
    std::thread proxy_service_thread(ProxyService);
    handler_ -> RunHandlerService();
    proxy_service_thread.join();
}

bool Proxy::ProxyService()
{


}