
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "utils/log.h"
#include "ace_socket/group.h"
#include "ace_socket/participant.h"


namespace wenet{

bool GroupManager::JoinGroup(string uuid, Participant* pa)
{
    if(uuid_map_.count(uuid))
    {
        // multiple clients
        uuid_map_[uuid]->Join(pa);
        pa->set_uuid_(uuid);
        return true;
    }
    return false;
}

bool GroupManager::JoinNewGroup(Participant* pa)
{
    // first client
    std::string uuid = GenerateUuid();
    Group* group = new Group();
    group->Join(pa);
    uuid_map_.insert({uuid, group});
    pa->set_uuid_(uuid);
    return true;
}

std::string GroupManager::GenerateUuid()
{
    boost::uuids::random_generator gen;
    boost::uuids::uuid id = gen();
    return boost::uuids::to_string(id);
}

void Group::Join(Participant* client){
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