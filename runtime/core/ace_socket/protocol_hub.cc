#include "protocol_hub.h"

int ProtocolHub::ProcessRequest(const std::string& buffer)
{
        //const char record_begin[9] = ;
    if (true == on_socket_pcm_)
    {
        assert(false == on_websocket_);
        //std::cout << "INFO receving pcm data..." << buffer << std::endl;
        // memcpy(pcm_buf_[buf_idx_++], buf, rev);
        // last_rev_ = rev;
        printf("INFO receving string size: %ld\n", buffer.size());
        all_pcm_data_.append(buffer);
        printf("INFO all_pcm_data_ size: %ld\n\n\n", all_pcm_data_.size());

        
    }
    else if (true == on_websocket_)
    {
        assert(false == on_socket_pcm_);
        printf("INFO receving websocket data...\n");
    }
    else{
        // char str[PROTOCOL_POS+1];
        // strncpy(str, buf, PROTOCOL_POS);

        // str[PROTOCOL_POS+1] = '\0';
        //printf("str is %s\n", str);
        std::string head = buffer.substr(0, 9);
        if (head == "suuiduuid")
        {
            printf("开始录音，收到配置信息\n");
            on_socket_pcm_ = true;
        }
        else if(head == "euuiduuid")
        {
            printf("结束录音\n");
            on_socket_pcm_ = false;
        }
        else
        {
            printf("使用websocket或者http服务\n");
            on_websocket_  = true;
        }
    }

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
    return 0;
 }