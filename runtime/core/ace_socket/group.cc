
#include "utils/log.h"
#include "ace_socket/group.h"
#include "ace_socket/participant.h"


namespace wenet{

bool GroupManager::JoinGroupManager(string uuid, Participant* pa)
{
    if(!uuid_map_.count(uuid))
    {
        // first client
        Group* group = new Group();
        group->Join(pa);
        uuid_map_.insert({uuid, group});
        return true;
    }
    else
    {
        // multiple clients
        uuid_map_[uuid]->Join(pa);
        return true;
    }
    return false;
}

void Group::Join(Participant* client){
    PLOG(INFO) << "new client join  " << client->get_hub_()->get_client_uuid_();
    clients_.push_back(client);
}

int Group::Leave(Participant* client){
    for(auto iter = clients_.begin(); iter != clients_.end(); ++iter)
    {
        if (*iter == client)
        {
            clients_.erase(iter);
            printf("INFO remove client %p", client);
            return 0;
        }
    }
    return -1;
}

void Group::BroadcastMessage(const std::string& message){
    for(auto cl : clients_)
    {
        PLOG(INFO) << "此处需要通过client的socket() send()向所有客户端广播消息";
    }
}

} // namespace wenet