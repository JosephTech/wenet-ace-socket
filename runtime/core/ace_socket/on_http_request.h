# include "ace_socket/hub_state.h"

namespace wenet{

void OnHttpRequest::Enter(ProtocolHub* ph, const std::string& buffer)
{
    RequestHttp = ParseHttpRequest(buffer);
    PLOG(TODO) << "OnHttpRequest::Enter()需要解析http请求,判断是否升级到websocket";
    return;
}

void OnHttpRequest::Execute(ProtocolHub* ph, const std::string& buffer)
{
    return;
}

void OnHttpRequest::Exit(ProtocolHub* ph)
{
    return;
}

RequestHttp OnHttpRequest::ParseHttpRequest(std::string& buffer)
{
    RequestHttp rh;
    return rh;
}

} // namespace wenet