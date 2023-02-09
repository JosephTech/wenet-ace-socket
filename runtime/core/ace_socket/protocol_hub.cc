#include "ace_socket/protocol_hub.h"

#include "boost/json/src.hpp"
#include "utils/log.h"

namespace wenet{

namespace json = boost::json;

// int ProtocolHub::ProcessRequest(const std::string& buffer)
int ProtocolHub::ProcessRequest(const char* buf, ssize_t rev)
{
    //const char record_begin[9] = ;
    std::string buffer(buf,rev);

    // 处理每次新的buffer，切换，放在->enter(中)
    hub_state_->Execute(this, buffer);

    // TODO: 状态： on_pcm, 
    // LOG(INFO) << "通信状态: " << connection_state_;
    // switch(connection_state_)
    // {
    //   case kOnFirstTimeConnect:
    //     LOG(INFO) << "TODO: 不是socket起始信号和配置，就是http 请求";
    //     std::string head = buffer.substr(0, 9);
    //     if (head == "suuiduuid")
    //     {
    //       on_socket_ = true;
    //       connection_state_ = kOnPcmData;
    //       string config = "配置信息"；
    //       OnSpeechStart(config);
    //     }
    //     else
    //     {
    //       connection_state_ = kOnHttpRequest;
    //       LOG(INFO) << "TODO: 处理http请求 把请求传递给http server"；
    //     }
    //     break;
    //   case kOnPcmData:
    //     LOG(INFO) << "TODO: 不是socket/websocket 结束信号，就是pcm数据";
    //     if(head == "euuiduuid")
    //     {
    //       printf("socket结束录音\n");
    //     }
    //     else
    //     {
    //       LOG(INFO) << "TODO: 不是socket/websocket 结束信号, 切换到wait状态";
    //     }
    //     break;
    //   case kOnHttpRequest:
    //     LOG(INFO) << "TODO: 把请求传递给http server"； 
    //     LOG(INFO) << "TODO: 不是http 请求，就是需要更新到websocket协议";
    //     LOG(INFO) << "TODO: 如果更新websocket协议，就改 形参&connection_state_"；
    //     LOG(INFO) << "TODO: 如果更新websocket协议，就改 形参&connection_state_"；
    //     break;
    //   case kOnWebSocket:
    //     on_websocket_ = true;
    //     LOG(INFO) << "TODO: 不是开始信号和配置，就是raw pcm数据";
    //     break;
    //   case kOnWaitResult:
    //     break;
    //   // case kOnWaitSocketResult:
    //   //   break;
    //   // case kOnWaitWebsocketResult:
    //   //   break;
    //   // case kOnIdle:
    //   //   if(on_socket_)
    //   //   {

    //   //   }
    //   //   else if (on_websocket_)
    //   //   {

    //   //   }
    //   //   break;
    // }

    // if (true == on_socket_pcm_)
    // {
    //     assert(false == on_websocket_);
    //     //std::cout << "INFO receving pcm data..." << buffer << std::endl;
    //     // memcpy(pcm_buf_[buf_idx_++], buf, rev);
    //     // last_rev_ = rev;
        
    //     //printf("INFO receving string size: %ld\n", buffer.size());
    //     if(record_pcm_)
    //     {
    //         all_pcm_data_.append(buffer);
    //     }
    //     //printf("INFO all_pcm_data_ size: %ld\n\n\n", all_pcm_data_.size());

        
    //     OnSpeechData(buffer);
    // }
    // else if (true == on_websocket_)
    // {
    //     assert(false == on_socket_pcm_);
    //     printf("INFO receving websocket data...\n");
    // }
    // else
    // {
    //     // char str[PROTOCOL_POS+1];
    //     // strncpy(str, buf, PROTOCOL_POS);

    //     // str[PROTOCOL_POS+1] = '\0';
    //     //printf("str is %s\n", str);
    //     std::string head = buffer.substr(0, 9);
    //     if (head == "suuiduuid")
    //     {
    //         OnSpeechStart();
    //     }
    //     else if(head == "euuiduuid")
    //     {
    //         printf("结束录音\n");
    //         on_socket_pcm_ = false;
    //     }
    //     else
    //     {
    //         printf("使用websocket或者http服务\n");
    //         on_websocket_  = true;
    //     }
    // }

    return 0;
}


int ProtocolHub::ProcessRespond()
{
    return 0;
}

Recorder& ProtocolHub::get_recorder_()
{
    return recorder_;
}


std::string ProtocolHub::get_all_pcm_data_()
{
    return all_pcm_data_;
}


 int ProtocolHub::SavePcmFile()
 {
    recorder_.SavePcmFile(all_pcm_data_);
    //decode_thread_->join();
    return 0;
 }

 void ProtocolHub::OnSpeechData(const string& buffer)
 {
    int num_samples = buffer.length() / sizeof(int16_t);

    const int16_t* pcm_data = reinterpret_cast<const int16_t*>(buffer.data());
    //printf("INFO pcm_data is %hd\n", *pcm_data);

    feature_pipeline_->AcceptWaveform(pcm_data, num_samples);
 }

/*
  params: 配置json
  */
 void ProtocolHub::OnSpeechStart(const string& config)
 {    
    //LOG(INFO) << "Receive start signal.";
    // std::shared_ptr<FeaturePipelineConfig> feature_config(new FeaturePipelineConfig(80, 16000));
    // feature_config_ = std::move(feature_config);

    PLOG(INFO) << "todo:  ProtocolHub::OnSpeechStart()此处需向客户端发送开始信息\n";
    PLOG(INFO) << "todo: ProtocolHub::OnSpeechStart()此处需解析客户端配置信息\n";
    PLOG(INFO) << "配置json is: " << config;

    feature_pipeline_ = std::make_shared<FeaturePipeline>(*feature_config_);
    decoder_ = std::make_shared<AsrDecoder>(feature_pipeline_, decode_resource_, *decode_config_);
    // on_socket_ = true;
    hub_state_ = on_pcm_data_state_;
    PLOG(INFO) << "todo:  ProtocolHub::OnSpeechStart()此处需join()线程\n";
    decode_thread_ = std::make_shared<std::thread>(&ProtocolHub::DecodeThreadFunc, this);
    
 }

 void ProtocolHub::OnSpeechEnd()
 {
    if (feature_pipeline_)
    {
      feature_pipeline_->set_input_finished();
    }
 }


 void ProtocolHub::DecodeThreadFunc()
 {
    printf("TODO decode线程启动\n");
    try {
    while (true) {
      // //printf("TODO decode_线程正在解码..\n");
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      // if (decoder_->DecodedSomething()) {
      //     std::string result = SerializeResult(false);
      //     OnPartialResult(result);
      // }      
      DecodeState state = decoder_->Decode();

      if (state == DecodeState::kEndFeats) {
        decoder_->Rescoring();
        std::string result = SerializeResult(true);
        // OnFinalResult(result);
        // OnFinish();
        // stop_recognition_ = true;
        break;
      } else if (state == DecodeState::kEndpoint) {
        decoder_->Rescoring();
        std::string result = SerializeResult(true);
        // OnFinalResult(result);
        // // If it's not continuous decoding, continue to do next recognition
        // // otherwise stop the recognition
        // if (continuous_decoding_) {
        //   decoder_->ResetContinuousDecoding();
        // } else {
        //   OnFinish();
        //   stop_recognition_ = true;
        //   break;
        // }
      } else {
        if (decoder_->DecodedSomething()) {
          std::string result = SerializeResult(false);
          OnPartialResult(result);
        }
      }
    }
  } catch (std::exception const& e) {
    LOG(ERROR) << e.what();
  }
 }

void ProtocolHub::OnPartialResult(const std::string& result)
{
    printf("***********************************************************************识别结果：...\n");
    LOG(INFO) << "Partial result: " << result;
}

std::string ProtocolHub::SerializeResult(bool finish) {
  printf("INFO 正在序列化解析结果...\n");
  // json::array nbest;
  // for (const DecodeResult& path : decoder_->result()) {
  //   json::object jpath({{"sentence", path.sentence}});
  //   if (finish) {
  //     json::array word_pieces;
  //     for (const WordPiece& word_piece : path.word_pieces) {
  //       json::object jword_piece({{"word", word_piece.word},
  //                                 {"start", word_piece.start},
  //                                 {"end", word_piece.end}});
  //       word_pieces.emplace_back(jword_piece);
  //     }
  //     jpath.emplace("word_pieces", word_pieces);
  //   }
  //   nbest.emplace_back(jpath);

  //   if (nbest.size() == nbest_) {
  //     break;
  //   }
  // }
  // return json::serialize(nbest);
  return "";
}

} // namespace wenet
