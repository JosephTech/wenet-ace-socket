#ifndef HUB_STATE_H_
#define HUB_STATE_H_

#include <string>
#include <map>

// #include "ace_socket/protocol_hub.h"
#include "utils/log.h"

namespace wenet{

class ProtocolHub;

class HubState{
public:
    virtual ~HubState(){}
    virtual void Enter(ProtocolHub* ph, const std::string& buffer) = 0;
    virtual void Execute(ProtocolHub* ph, const std::string& buffer) = 0;
    virtual void Exit(ProtocolHub* ph) = 0;

private:
    
};

class FirstTimeConnect: public HubState{
public:
    FirstTimeConnect() = default;
    ~FirstTimeConnect(){}
    void Enter(ProtocolHub* ph, const std::string& buffer);
    void Execute(ProtocolHub* ph, const std::string& buffer);
    void Exit(ProtocolHub* ph);
};


class OnPcmData: public HubState{
public:
    OnPcmData() = default;
    ~OnPcmData(){}
    void Enter(ProtocolHub* ph, const std::string& buffer);
    void Execute(ProtocolHub* ph, const std::string& buffer);
    void Exit(ProtocolHub* ph);
};

struct RequestHttp{
    std::string method;                         //请求方法get、post等等
    std::string url;                            //请求路径
    std::string version;                        //协议版本
    std::string host;                           //主机
    std::string connection;                     //链接后续状态，是否升级协议
    std::string upgrade;                        //需要升级为什么协议
    std::string cookie;                         //cookie
	std::map<std::string, std::string> param;   //get请求的参数
	std::string sec_websocket_key;              //用于建立websocket协议
    std::string content;		                //主体内容
};

class OnHttpRequest: public HubState{
public:
    OnHttpRequest() = default;
    ~OnHttpRequest(){}
    void Enter(ProtocolHub* ph, const std::string& buffer);
    void Execute(ProtocolHub* ph, const std::string& buffer);
    void Exit(ProtocolHub* ph);
    RequestHttp ParseHttpRequest(std::string& buffer);
private:
};


} // namespace wenet

#endif /* HUB_STATE_H_ */