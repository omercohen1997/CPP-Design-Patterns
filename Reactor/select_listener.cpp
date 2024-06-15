#include <vector>

#include "select_listener.hpp"

FDListener::pairVector SelectListener::Listen(const std::unordered_map<std::pair<int, Operation>, std::function<void()>, HashFunc> &map_callbacks)
{
    fd_set readFds, writeFds, exceptFds;
    int maxFd = -1;
    FD_ZERO(&readFds);
    FD_ZERO(&writeFds);
    FD_ZERO(&exceptFds);

    for (auto &callback : map_callbacks)
    {
        int fd = callback.first.first;
        Operation operation = callback.first.second;

        if (operation == READ)
        {
            FD_SET(fd, &readFds);
        }
        else if (operation == WRITE)
        {
            FD_SET(fd, &writeFds);
        }
        else if (operation == EXCEPT)
        {
            FD_SET(fd, &exceptFds);
        }

        if (fd > maxFd)
        {
            maxFd = fd;
        }
    }

    int fdReady = select(maxFd + 1, &readFds, &writeFds, &exceptFds, NULL);
    if (-1 == fdReady)
    {
        throw std::runtime_error("select failed");
    }

    std::vector<std::pair<int, Operation>> vectReadyFds;
    for (const auto &callback : map_callbacks)
    {
        int fd = callback.first.first;
        Operation operation = callback.first.second;

        if ((operation == READ && FD_ISSET(fd, &readFds)) ||
            (operation == WRITE && FD_ISSET(fd, &writeFds)) ||
            (operation == EXCEPT && FD_ISSET(fd, &exceptFds)))
        {
            vectReadyFds.push_back(std::make_pair(fd, operation));
        }
    }

    return vectReadyFds;
}
