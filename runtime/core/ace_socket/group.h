#include <string>
#include <vector>
#include <unordered_map>

namespace wenet{

class Participant;

//
//  each uuid has a Group that manage socket client and websocket client with same uuid. 
//
class Group{
public:
    void Join(Participant* client);
    int Leave(Participant* client);
    void BroadcastMessage(const std::string& message);
private:
    std::vector<Participant*> clients_ = std::vector<Participant*>(3);
};

//
//  key: uuid, value: group
//
class GroupManager{
private:
    GroupManager(){
        
    }
    ~GroupManager(){}
    GroupManager(const GroupManager&);
    // GroupManager& operator=(const GroupManager&);
public:
    static GroupManager& Instance(){
        static GroupManager instance;
        return instance;
    }
    bool JoinGroupManager(string,Participant* pa);

private:
    std::unordered_map<std::string, Group*> uuid_map_ = {};
};



} // namespace wenet