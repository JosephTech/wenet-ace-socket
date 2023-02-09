#include "ace_socket/hub_state.h"
#include "ace_socket/protocol_hub.h"

namespace wenet{

void FirstTimeConnect::Enter(ProtocolHub* ph, const std::string& buffer)
{
    return;

}

void FirstTimeConnect::Execute(ProtocolHub* ph, const std::string& buffer)
{
    PLOG(INFO) << "FirstTimeConnect::execute()";
    // 
    PLOG(INFO) << "TODO: FirstTimeConnect::execute()不是socket起始信号和配置, 就是http 请求";
    std::string head = buffer.substr(0, 9);
    if (head == "suuiduuid")
    {
        PLOG(INFO) << "TODO: FirstTimeConnect::execute()切换为pcm_data状态";
        // ph->on_socket_ = true;
        // ph->connection_state_ = kOnPcmData;
        string config = buffer.substr(9);
        ph->set_on_socket_(true);
        ph->OnSpeechStart(config);
    }
    else
    {
        // ph->connection_state_ = kOnHttpRequest;
        PLOG(INFO) << "TODO: 处理http请求 把请求传递给http server";
        // ph->states_machine_[ph->connection_state_]->Enter(ph, buffer);
    }

    return;
}


void FirstTimeConnect::Exit(ProtocolHub* ph)
{
    return;
}

} // namespace wenet