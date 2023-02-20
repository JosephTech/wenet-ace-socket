#ifndef WAITENDTHREADS_H_
#define WAITENDTHREADS_H_

#include <chrono>
#include <thread>

#include "utils/log.h"

#include <mutex>

namespace wenet{

class Participant;

// 
// 解决阻塞问题，若handle_close()被Reactor调用时仍正在解码，则进入此队列等待。待解码完成，再次调用handle_close()
//
class WaitEndThreads{
private:
    WaitEndThreads(){}
    ~WaitEndThreads(){}
    // WaitEndThreads(const WaitEndThreads&);
    // WaitEndThreads& operator=(const WaitEndThreads&);
public:
    static WaitEndThreads& Instance(){
        static WaitEndThreads instance;
        return instance;
    }
    void Update();
    void Add(Participant* cl);
private:
    void Check();
    std::set<Participant*> clients_;
    std::mutex mutex_;
};

} // namespace wenet

#endif /* WAITENDTHREADS_H_ */