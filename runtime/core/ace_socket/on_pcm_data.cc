# include "ace_socket/hub_state.h"
#include "ace_socket/protocol_hub.h"

namespace wenet{

void OnPcmData::Enter(ProtocolHub* ph, const std::string& buffer)
{
    return;
}
void OnPcmData::Execute(ProtocolHub* ph, const std::string& buffer)
{
    PLOG(INFO) << "TODO: OnPcmData::Execute() be called";
    if(ph->get_on_socket_())
    {
        std::string head = buffer.substr(0, 9);
        if(head == "euuiduuid")
        {
            PLOG(INFO) << "socket结束录音 发送等待解码完成，发送result到客户端\n";
            ph->get_decode_thread_()->join();
        }
        int num_samples = buffer.length() / sizeof(int16_t);
        const int16_t* pcm_data = reinterpret_cast<const int16_t*>(buffer.data());
        PLOG(INFO) << "Put pcm data into queue.";
        ph->get_feature_pipeline_()->AcceptWaveform(pcm_data, num_samples);
// void ProtocolHub::OnSpeechData(const string& buffer)
//  {
//     int num_samples = buffer.length() / sizeof(int16_t);

//     const int16_t* pcm_data = reinterpret_cast<const int16_t*>(buffer.data());
//     //printf("INFO pcm_data is %hd\n", *pcm_data);

//     feature_pipeline_->AcceptWaveform(pcm_data, num_samples);
//  }
    }
    else
    {
        PLOG(INFO) << "TODO: 是websocket, 等待pcm数据 或结束信号, 切换到wait状态";
    }
    return;
}
void OnPcmData::Exit(ProtocolHub* ph)
{
    return;
}
} // namespace wenet