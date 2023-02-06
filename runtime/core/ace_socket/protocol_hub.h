
#ifndef PROTOCOL_HUB_H_
#define PROTOCOL_HUB_H_

#include <cassert>
#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>

#include "recorder.h"
#include "frontend/feature_pipeline.h"
#include "decoder/asr_decoder.h"

class ProtocolHub{
public:
    int ProcessRequest(const std::string& request);
    int ProcessRespond();
    Recorder& get_recorder_();
    std::string get_all_pcm_data_();
    int SavePcmFile();

private:
    bool on_socket_pcm_ = true;
    bool on_websocket_ = false;
    std::string all_pcm_data_;
    Recorder recorder_;
};

#endif /* PROTOCOL_HUB_H_ */