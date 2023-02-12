#include <iterator>
#include <string.h>
#include <openssl/sha.h>

#include "ace_socket/hub_state.h"
#include "ace_socket/protocol_hub.h"
#include "ace_socket/participant.h"
#include "ace_socket/base64.h"

#include <chrono>
#include <thread>

namespace wenet{

void OnWebSocket::Enter(const std::string& buffer)
{
    RequestHttp rh = protocol_hub_->get_request_http_();
    PLOG(INFO) << "TODO(Joseph): 此处需计算base64(sha1(websocket_key + .....))";
    // 258EAFA5-E914-47DA-95CA-C5AB0DC85B11

    //string temp = rh.sec_websocket_key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    //unsigned const char ibuf[] = 
    
    // char w_key[rh.sec_websocket_key.length()+key.length()] = rh.sec_websocket_key.c_str();
    // const unsigned char temp[rh.sec_websocket_key.length()+key.length()] = strcat(w_key, key.c_str());

    // std::vector<BYTE> myData;
    // ...
    // std::string encodedData = base64_encode(&myData[0], myData.size());
    // std::vector<BYTE> decodedData = base64_decode(encodedData);

    char temp[128];
    
    unsigned char obuf[20];
    string key = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    strcpy(temp, rh.sec_websocket_key.c_str());
    PLOG(INFO) << "temp is " << temp;
    strcat(temp, key.c_str());
    PLOG(INFO) << "temp is" << temp;
    const unsigned char* ibuf = (const unsigned char*)temp;

    int len = rh.sec_websocket_key.length() + key.length();
    SHA1(ibuf, len, obuf);
    // 
    PLOG(INFO) << "************************";
    for(int i = 0; i < 20; ++i)
    {
        std::cout << std::hex << int(obuf[i]);
    }
    std::cout << std::endl;

    std::vector<BYTE> sha1_res(std::begin(obuf), std::end(obuf));
    std::string SecWebSocketAccept = base64_encode(&sha1_res[0], sha1_res.size());
    
    PLOG(INFO) << "SecWebSocketAccept is " << SecWebSocketAccept;

    std::string response;
    response.append("HTTP/1.1 101 Switching Protocols\r\n");
	response.append("Upgrade: websocket\r\n");
    response.append("Connection: Upgrade\r\n");
	response.append("Sec-WebSocket-Accept:" + SecWebSocketAccept + "\r\n");
    response.append("\r\n");
    
    PLOG(INFO) << "websocket server response is "<< response;

    if(-1 == protocol_hub_->get_client_()->socket().send_n(response.c_str(), response.length()))
    {
        //protocol_hub_->get_client_()->handle_close(ACE_INVALID_HANDLE, 0);
        PLOG(ERROR) << "websocket response error.";
    }
    // for(int i = 0; i < 100; ++i)
    // {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // }

    PLOG(INFO) << "发送成功" ;

}

void OnWebSocket::Execute(const std::string& buffer)
{
    PLOG(INFO) << "TODO(Joseph): websocket数据处理";
    PLOG(INFO) << "websocket receive: " << buffer;
}

} // namespace wenet