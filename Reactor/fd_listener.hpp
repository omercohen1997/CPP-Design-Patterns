#ifndef FD_LISTENER_HPP
#define FD_LISTENER_HPP

#include <unordered_map>
#include <vector>
#include <functional>

class FDListener
{
public:
    enum Operation
    {
        WRITE,
        READ,
        EXCEPT
    };
    typedef std::vector<std::pair<int, FDListener::Operation>> pairVector;

    class HashFunc
    {
    public:
        std::size_t operator()(const std::pair<int, Operation> &p) const
        {
            auto hash1 = std::hash<int>{}(p.first);
            auto hash2 = std::hash<Operation>{}(p.second);

            if (hash1 != hash2)
            {
                return hash1 ^ hash2;
            }

            return hash1;
        }
    };

    virtual ~FDListener() {}
    virtual pairVector Listen(const std::unordered_map<std::pair<int, Operation>, std::function<void()>, HashFunc> &map_callbacks) = 0;
};

#endif // FD_LISTENER_HPP