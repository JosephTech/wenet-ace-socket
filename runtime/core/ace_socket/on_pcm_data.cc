# include "ace_socket/hub_state.h"
#include "ace_socket/protocol_hub.h"

namespace wenet{

void OnPcmData::Enter(const std::string& buffer)
{
    return;
}
void OnPcmData::Execute(const std::string& buffer)
{
    //PLOG(INFO) << "TODO: OnPcmData::Execute() be called";
    if(protocol_hub_->get_on_socket_())
    {
        // socket pcm
        int head_len = 3 + 36;
        int uuid_len = 36;
        std::string uuid = buffer.substr(3, uuid_len);
        std::string signal;
        signal.push_back(buffer[0]);

        PLOG(INFO) << "uuid is " << uuid;
        PLOG(INFO) << "signal is " << signal;

        if (signal == "e" && uuid == protocol_hub_->get_client_uuid_())
        {
            PLOG(INFO) << "OnPcmData::Execute() socket结束录音,向decoder发送停止信号, 发送等待解码完成，发送result到客户端\n";
            // protocol_hub_->OnSpeechEnd();
            protocol_hub_->HandleClose();  // 切换为wait result状态，等待对端关闭即可
            PLOG(INFO) << "在handle_close()时候,join()线程";
            // protocol_hub_->get_decode_thread_()->join();
        }
        int num_samples = buffer.length() / sizeof(int16_t);
        const int16_t* pcm_data = reinterpret_cast<const int16_t*>(buffer.data());
        //PLOG(INFO) << "Put pcm data into queue.";
        protocol_hub_->get_feature_pipeline_()->AcceptWaveform(pcm_data, num_samples);
// void ProtocolHub::OnSpeechData(const string& buffer)
//  {
//     int num_samples = buffer.length() / sizeof(int16_t);

//     const int16_t* pcm_data = reinterpret_cast<const int16_t*>(buffer.data());
//     //printf("INFO pcm_data is %hd\n", *pcm_data);

//     feature_pipeline_->AcceptWaveform(pcm_data, num_samples);
//  }
    }
    else if (protocol_hub_->get_on_websocket_())
    {
        // websocket pcm
        PLOG(INFO) << "websocket pcm也 有可能是websocket结束信号";

    }
    return;
}
void OnPcmData::Exit()
{
    return;
}
} // namespace wenet