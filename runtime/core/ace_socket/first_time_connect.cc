#include "ace_socket/hub_state.h"
#include "ace_socket/protocol_hub.h"
#include "ace_socket/group.h"

namespace wenet{

void FirstTimeConnect::Enter(const std::string& buffer)
{
    return;

}

void FirstTimeConnect::Execute(const std::string& buffer)
{
    PLOG(INFO) << "FirstTimeConnect::execute()";
    // 
    PLOG(INFO) << "TODO: FirstTimeConnect::execute()不是socket起始信号和配置, 就是http 请求";
    std::string head = buffer.substr(0, 9);
    if (head == "suuiduuid")
    {
        // ph->on_socket_ = true;
        // ph->connection_state_ = kOnPcmData;
        string uuid = "uuiduuid";
        bool ret = GroupManager::Instance().JoinGroupManager(uuid, protocol_hub_->get_client_());    
        if(!ret)
        {
            PLOG(INFO) << "FirstTimeConnect::Execute(), client join failed";
        }
        PLOG(INFO) << "TODO: FirstTimeConnect::execute()切换为pcm_data状态";
        string config = buffer.substr(9);
        protocol_hub_->set_on_socket_(true);
        protocol_hub_->OnSpeechStart(config);
    }
    else
    {
        // ph->connection_state_ = kOnHttpRequest;
        PLOG(INFO) << "TODO: 处理http请求 把请求传递给http server";
        // ph->states_machine_[ph->connection_state_]->Enter(ph, buffer);
    }

    return;
}


void FirstTimeConnect::Exit()
{
    return;
}

// void FirstTimeConnect::OnSpeechStart(const std::string& config)
// {
//     PLOG(INFO) << "todo:  ProtocolHub::OnSpeechStart()此处需向客户端发送开始信息\n";
//     PLOG(INFO) << "todo: ProtocolHub::OnSpeechStart()此处需解析客户端配置信息\n";
//     PLOG(INFO) << "配置json is: " << config;

//     protocol_hub_->get_feature_pipeline_() = std::make_shared<FeaturePipeline>(*feature_config_);
//     decoder_ = std::make_shared<AsrDecoder>(protocol_hub_->get_feature_pipeline_(), decode_resource_, *decode_config_);
//     // on_socket_ = true;
//     // protocol_hub_->get_hub_state_() = on_pcm_data_state_;
//     protocol_hub_->ChangeHubState(kOnPcmData, config);
//     protocol_hub_->RunDecodeThread();
//     PLOG(INFO) << "todo:  ProtocolHub::OnSpeechStart()此处需join()线程\n";
//     // decode_thread_ = std::make_shared<std::thread>(&ProtocolHub::DecodeThreadFunc, protocol_hub_);
// }

// void FirstTimeConnect::PassConfigs(std::shared_ptr<FeaturePipelineConfig> feature_config,
//                                     std::shared_ptr<DecodeOptions> decode_config,
//                                     std::shared_ptr<DecodeResource> decode_resource)
// {
//     feature_config_ = std::move(feature_config);
//     decode_config_ = std::move(decode_config);
//     decode_resource_ = std::move(decode_resource);
// }

} // namespace wenet