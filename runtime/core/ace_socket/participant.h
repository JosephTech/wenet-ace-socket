#ifndef PARTICIPANT_H_
#define PARTICIPANT_H_
#include <ace/Reactor.h>
#include <ace/Event_Handler.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Log_Msg.h>
#include <cassert>
#include <fstream>
#include <sstream>

#include "ace_socket/protocol_hub.h"
// class ProtocolHub;

#define MAX_BUF_LEN 1024 

namespace wenet{



class Participant: public ACE_Event_Handler{
public:
    Participant(std::shared_ptr<FeaturePipelineConfig> feature_config,
                        std::shared_ptr<DecodeOptions> decode_config,
                        std::shared_ptr<DecodeResource> decode_resource)
            :
            feature_config_(std::move(feature_config)),
            decode_config_(std::move(decode_config)),
            decode_resource_(std::move(decode_resource)){}
    ~Participant();
    
    int open();
    int handle_input(ACE_HANDLE handle = ACE_INVALID_HANDLE);
    int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
    // void pass_configs(std::shared_ptr<FeaturePipelineConfig> feature_config,
    //                     std::shared_ptr<DecodeOptions> decode_config,
    //                     std::shared_ptr<DecodeResource> decode_resource);
    ACE_SOCK_Stream& socket(){return sock_;}
    ACE_HANDLE get_handle () const
        { return sock_.get_handle (); }

// private:
//     int SavePcmFile();
private:
    ACE_SOCK_Stream sock_;
    // bool on_pcm_ = true;
    // bool on_websocket_ = false;
    // char pcm_buf_[1024][1024];  // 需限制录制时长
    // int buf_idx_ = 0;
    // int last_rev_ = 0;           // 最后一次收到的pcm数据长度

    std::shared_ptr<FeaturePipelineConfig> feature_config_;
    std::shared_ptr<DecodeOptions> decode_config_;
    std::shared_ptr<DecodeResource> decode_resource_;

    ProtocolHub* hub_ = nullptr;
};

} // namespace wenet

#endif /* PARTICIPANT_H_ */

#define PROTOCOL_POS 9