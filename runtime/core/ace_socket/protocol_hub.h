#ifndef PROTOCOL_HUB_H_
#define PROTOCOL_HUB_H_

#include <cassert>
#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <unordered_map>



#include "utils/log.h"

#include "frontend/feature_pipeline.h"
#include "decoder/asr_decoder.h"

#include "ace_socket/recorder.h"
#include "ace_socket/hub_state.h"


namespace wenet{
    
// enum CommunicationState
// {    
//     kOnFirstTimeConnect,                // http header or socket protocol data with start signal and configs.
//     kOnPcmData,                         // receive socket end signal or websocket end signal or continue put pcm data into feature_pipeline_ queue.
//     kOnHttpRequest,                     // whether http request or need update to websocket protocol.
//     kOnWebSocket,                       // receive pcm data or start signal and configs.
//     kOnWaitResult,                      // waitting decode result.
//     // kOnWaitSocketResult,             // waitting socket decode result，can't receive new request until SocketResultSent event.
//     // kOnWaitWebsocketResult,          // watiting websocket decode result, can't receive new request until WebsocketResultSent event.
//     // kOnIdle,                         // keep socket/websocket connection, wait for the next speech.
// };

// class ProtocolHub;  // 前置声明




// class HubState;  // 前置声明
// class FirstTimeConnect;

class ProtocolHub{
public:
    ProtocolHub(std::shared_ptr<FeaturePipelineConfig> feature_config,
                        std::shared_ptr<DecodeOptions> decode_config,
                        std::shared_ptr<DecodeResource> decode_resource):
            feature_config_(std::move(feature_config)),
            decode_config_(std::move(decode_config)),
            decode_resource_(std::move(decode_resource)){
                // OnSpeechStart("");                
                // states_machine_[kOnFirstTimeConnect]->enter(this);
                first_connect_state_ = new FirstTimeConnect();
                on_pcm_data_state_ = new OnPcmData();
                // on_http_request_state_ = new OnHttpRequest();
                hub_state_ = first_connect_state_;
            }

    ~ProtocolHub(){}
            
    int ProcessRequest(const char* buf, ssize_t rev);
    int ProcessRespond();
    Recorder& get_recorder_();
    int SavePcmFile();
    void OnSpeechData(const string& buffer);
    void OnSpeechStart(const string& config);
    void OnSpeechEnd();
    void DecodeThreadFunc();
    void OnPartialResult(const std::string& result);
    std::string SerializeResult(bool finish);

    std::string get_all_pcm_data_();
    bool get_record_pcm_(){return record_pcm_;}
    void set_on_socket_(bool flag){on_socket_ = flag;}
    bool get_on_socket_(){return on_socket_;}
    std::shared_ptr<FeaturePipeline>& get_feature_pipeline_(){return feature_pipeline_;}
    std::shared_ptr<std::thread>& get_decode_thread_(){return decode_thread_;}


private:
    bool on_socket_ = false;
    bool on_websocket_ = false;             // connection state.
    bool record_pcm_ = false;               // whether to save the pcm data.

    int nbest_ = 1;
    std::string all_pcm_data_;
    Recorder recorder_;

    //std::unordered_map<CommunicationState, HubState*> states_machine_;

    std::shared_ptr<FeaturePipelineConfig> feature_config_;
    std::shared_ptr<DecodeOptions> decode_config_;
    std::shared_ptr<DecodeResource> decode_resource_;
    
    std::shared_ptr<FeaturePipeline> feature_pipeline_ = nullptr;
    std::shared_ptr<AsrDecoder> decoder_ = nullptr;
    std::shared_ptr<std::thread> decode_thread_ = nullptr;

    // CommunicationState connection_state_ = kOnFirstTimeConnect;

    HubState* hub_state_;
    FirstTimeConnect* first_connect_state_;
    OnPcmData* on_pcm_data_state_;
    // OnHttpRequest* on_http_request_state_;
};


} // namespace wenet

#endif /* PROTOCOL_HUB_H_ */