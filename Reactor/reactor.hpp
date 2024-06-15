#ifndef REACTOR_HPP
#define REACTOR_HPP

#include <functional>       //  std::function
#include <unordered_map>    //  std::unordered_map
#include <memory>           // unique_ptr

#include "fd_listener.hpp"

  
class Reactor
{ 
public:

    Reactor();
    ~Reactor() = default;

    Reactor(const Reactor& other_) = delete;
    Reactor(const Reactor&& other_) = delete;
    Reactor& operator=(const Reactor& other_) = delete;
    Reactor& operator=(const Reactor&& other_) = delete;
    
    void Run(); // blocking 
    void Stop();
    void Add(int fd_, FDListener::Operation op_, std::function<void()> callback_);
    void Remove(int fd_, FDListener::Operation op_);
   
private:
    std::unordered_map<std::pair<int, FDListener::Operation>, std::function<void()>, FDListener::HashFunc> m_callbacks;
   std::unique_ptr<FDListener> m_listener;
    bool m_IsStop;
};



#endif // REACTOR_HPP
