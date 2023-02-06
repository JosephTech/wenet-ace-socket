#include "participant_acceptor.h"
#include "participant.h"

ParticipantAcceptor::~ParticipantAcceptor(){
    handle_close(ACE_INVALID_HANDLE, 0);
}

int ParticipantAcceptor::open (const ACE_INET_Addr &listen_addr)
{
    if (this->acceptor_.open (listen_addr, 1) == -1)
    {
        printf("open port fail\n");
        return -1;
    }
    //注册接受连接回调事件
    return this->reactor ()->register_handler(this, ACE_Event_Handler::ACCEPT_MASK);
}

int ParticipantAcceptor::handle_input (ACE_HANDLE fd )
{
    printf("ParticipantAcceptor::handle_input()被调用..\n");
    Participant *client = new Participant();
    //auto_ptr<ClientService> p (client);

    if (this->acceptor_.accept (client->socket ()) == -1)
    {
        printf("accept client fail\n");
        return -1;
    }
    //p.release ();
    client->reactor (this->reactor ());
    if (client->open () == -1)
        client->handle_close (ACE_INVALID_HANDLE, 0);
    return 0;
}
// int ParticipantAcceptor::handle_input(ACE_HANDLE fd){
//     printf("ParticipantAcceptor::handle_input()被调用..\n");
//     //ACE_DEBUG((LM_CRITICAL, ACE_TEXT("ACCEPT, new client fking!!!!!!!!!!!\n")));

//     Participant* client = new Participant();

//     printf("accept等待客户端连接...\n");
//     // accept阻塞等待，等待客户端连接
//     if (acceptor_.accept(client->socket()) == -1){
//         printf("accept client failed");
//         return -1;
//     }

//     client->reactor(this->reactor());
//     if(client->open() == -1){
//         client->handle_close(ACE_INVALID_HANDLE, 0);
//         //ACE_ERROR_RETURN((LM_ERROR, "%p\n", "acceptor_.accept()"), -1);
//     }
    
//     // else{
//     //     通信成功，需要在particapant::handle_input()中处理业务
//     //     可以在此处加入聊天室等
//     // }
//     // 需要stream pool 存储所有clients, ParticipantAcceptor析构 的时候，要清理stream_pool
//     // 
//     // 这里可以加个decorder，每个decorder服务于一个client  从队列中获取  1024的pcm数据，进行处理（比如拼接成pcm文件）
//     // 
//     // （没必要）main函数那边，可以加个线程池，用于接受客户端的连接（acceptor），每个线程都run_event_loop()了，所以是每个线程都有一个reactor()
    
//     return 0;
// }

int ParticipantAcceptor::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask m){
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("ParticipantAcceptor::handle_close()被调用..\n")));
    if(acceptor_.get_handle() != ACE_INVALID_HANDLE){
        ACE_Reactor_Mask mask = ACE_Event_Handler::ACCEPT_MASK | ACE_Event_Handler::DONT_CALL;

        reactor()->remove_handler(this, mask);
        acceptor_.close();
    }
    return 0;

}
