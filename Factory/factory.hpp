
#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <unordered_map> //  std::unordered_map
#include <functional>    //  std::function
#include <memory>        //  std::shared_ptr
#include <string>        //  string

template <typename RetType, typename Key, typename... ARGS>
class Factory
{
public:
    Factory() = default;
    ~Factory() = default;
    typedef std::function<std::shared_ptr<RetType>(ARGS...)> UserFunc_t;

    std::shared_ptr<RetType> Create(const Key &key_, ARGS... args_) const; // may throw

    void Add(Key key_, UserFunc_t func_); // may throw

private:
    std::unordered_map<Key, UserFunc_t> m_map;

}; // Factory

template <typename RetType, typename Key, typename... ARGS>
std::shared_ptr<RetType> Factory<RetType, Key, ARGS...>::Create(const Key &key_, ARGS... args_) const
{
    return m_map.at(key_)(args_...);
}

template <typename RetType, typename Key, typename... ARGS>
void Factory<RetType, Key, ARGS...>::Add(Key key_, UserFunc_t func_)
{
    if (nullptr == func_)
    {
        throw std::invalid_argument("Function cannot be NULL\n");
    }

    m_map[key_] = func_;
}

#endif /* ILRD_RD147_148_FACTORY_HPP */
