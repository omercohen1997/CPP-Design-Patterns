/****************************************/
/*                                      */
/*   Student: 	Omer Cohen	            */
/*   Project:   reactor                 */
/*   Date:      19/2/2024               */
/*   Reviewer:                          */
/*                                      */
/****************************************/

#include <vector>

#include "reactor.hpp"
#include "select_listener.hpp"


namespace ilrd
{   
    
    Reactor::Reactor() : m_listener(new SelectListener), m_IsStop(false) {}

    /************************************************************************/
    
    void Reactor::Run() 
    {
        while (!m_IsStop)
        {
            FDListener::pairVector readyFds = m_listener->Listen(m_callbacks); 

            for (const auto& readyFd : readyFds)
            {
                auto callback = m_callbacks.find(readyFd);
                if (callback != m_callbacks.end())
                {
                    callback->second();
                    if(false == m_IsStop)
                    {
                        break;
                    }
                }
            }
        }
    }

    /************************************************************************/

    void Reactor::Add(int fd_, FDListener::Operation op_, std::function<void()> callback_)
    {
        m_callbacks[std::make_pair(fd_, op_)] = callback_;
    }

    /************************************************************************/

    void Reactor::Remove(int fd_, FDListener::Operation op_)
    {
        m_callbacks.erase(std::make_pair(fd_, op_));
    }

    /************************************************************************/
    void Reactor::Stop()
    {
        m_IsStop = true;
    }


} // ilrd
