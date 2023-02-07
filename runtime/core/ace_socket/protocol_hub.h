
#ifndef PROTOCOL_HUB_H_
#define PROTOCOL_HUB_H_

#include <cassert>
#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

#include "ace_socket/recorder.h"
#include "frontend/feature_pipeline.h"
#include "decoder/asr_decoder.h"
#include "utils/log.h"


namespace wenet{

class ProtocolHub{
public:
    ProtocolHub(std::shared_ptr<FeaturePipelineConfig> feature_config,
                        std::shared_ptr<DecodeOptions> decode_config,
                        std::shared_ptr<DecodeResource> decode_resource):
            feature_config_(std::move(feature_config)),
            decode_config_(std::move(decode_config)),
            decode_resource_(std::move(decode_resource)){
                OnSpeechStart();
            }

    ~ProtocolHub(){}
            
    int ProcessRequest(const char* buf, ssize_t rev);
    int ProcessRespond();
    Recorder& get_recorder_();
    std::string get_all_pcm_data_();
    int SavePcmFile();
    void OnSpeechData(const string& buffer);
    void OnSpeechStart();
    void DecodeThreadFunc();
    void OnPartialResult(const std::string& result);
    std::string SerializeResult(bool finish);

private:
    bool on_socket_pcm_ = false;
    bool on_websocket_ = false;
    std::string all_pcm_data_;
    Recorder recorder_;

    std::shared_ptr<FeaturePipelineConfig> feature_config_;
    std::shared_ptr<DecodeOptions> decode_config_;
    std::shared_ptr<DecodeResource> decode_resource_;
    
    std::shared_ptr<FeaturePipeline> feature_pipeline_ = nullptr;
    std::shared_ptr<AsrDecoder> decoder_ = nullptr;
    std::shared_ptr<std::thread> decode_thread_ = nullptr;

    int nbest_ = 1;
};

} // namespace wenet

#endif /* PROTOCOL_HUB_H_ */