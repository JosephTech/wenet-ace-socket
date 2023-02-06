#ifndef PARTICIPANTACCEPTOR_H_
#define PARTICIPANTACCEPTOR_H_

#include <ace/Reactor.h>
#include <ace/Event_Handler.h>
#include <ace/SOCK_Acceptor.h>

#include "participant.h"
#include "recorder.h"

class ParticipantAcceptor: public ACE_Event_Handler{
public:
    ~ParticipantAcceptor();

    int open(const ACE_INET_Addr &listen_addr);
    ACE_HANDLE get_handle () const
        { return this->acceptor_.get_handle (); }
    int handle_input (ACE_HANDLE fd);
    int handle_close (ACE_HANDLE handle,
                        ACE_Reactor_Mask close_mask);

private:
    ACE_SOCK_Acceptor acceptor_;

};

#endif /* PARTICIPANTACCEPTOR_H_ */