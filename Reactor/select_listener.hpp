#ifndef SELECT_LISTENER_HPP
#define SELECT_LISTENER_HPP

#include "fd_listener.hpp"

#include <sys/select.h>

class SelectListener : public FDListener
{
public:
    virtual pairVector Listen(const std::unordered_map<std::pair<int, Operation>, std::function<void()>, HashFunc> &map_callbacks);
};

#endif // SELECT_LISTENER_HPP