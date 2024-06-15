#ifndef IILRD_RD147_SELECT_LISTENER_HPP
#define IILRD_RD147_SELECT_LISTENER_HPP

#include "fd_listener.hpp"

#include <sys/select.h>
namespace ilrd
{

    class SelectListener : public FDListener
    {
    public:
        virtual pairVector Listen(const std::unordered_map<std::pair<int, Operation>, std::function<void()>, HashFunc> &map_callbacks);
    };

} // ilrd

#endif // IILRD_RD147_SELECT_LISTENER_HPP