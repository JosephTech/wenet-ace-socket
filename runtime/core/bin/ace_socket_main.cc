#include<ace/Reactor.h>
#include<ace/Log_Msg.h>
#include "participant_acceptor.h"

int main(int argc, char *argv[]) 
{
    ACE_INET_Addr addr(7890);
    ParticipantAcceptor server;
    server.reactor(ACE_Reactor::instance());
    if(-1 == server.open(addr))
    {
        ACE_DEBUG((LM_ERROR, ACE_TEXT("ERROR: The port is occupied.\n")));
    }
    
    ACE_DEBUG((LM_INFO, ACE_TEXT("INFO: run reactor event loop.\n")));
    ACE_Reactor::instance()->run_reactor_event_loop();
 
    return 0; 
} 
 