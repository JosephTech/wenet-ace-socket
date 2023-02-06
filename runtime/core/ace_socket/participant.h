#ifndef PARTICIPANT_H_
#define PARTICIPANT_H_
#include <ace/Reactor.h>
#include <ace/Event_Handler.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Log_Msg.h>
#include <cassert>
#include <fstream>
#include <sstream>

#include "protocol_hub.h"

#define MAX_BUF_LEN 1024 


class Participant: public ACE_Event_Handler{
public:
    ~Participant(){};
    
    int open();
    ACE_HANDLE get_handle () const
        { return sock_.get_handle (); }
    int handle_input(ACE_HANDLE handle = ACE_INVALID_HANDLE);
    int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
    ACE_SOCK_Stream& socket(){return sock_;}
// private:
//     int SavePcmFile();
private:
    ACE_SOCK_Stream sock_;
    bool on_pcm_ = true;
    bool on_websocket_ = false;
    char pcm_buf_[1024][1024];  // 需限制录制时长
    int buf_idx_ = 0;
    int last_rev_ = 0;           // 最后一次收到的pcm数据长度
    ProtocolHub hub_;
};

#endif /* PARTICIPANT_H_ */

#define PROTOCOL_POS 9