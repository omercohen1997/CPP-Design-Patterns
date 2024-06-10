#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <atomic> // atomic
#include <mutex>  // mutex

    template <typename T>
    class Singleton
    {
    public:
        static T *GetInstance();

        ~Singleton() = delete;
        Singleton() = delete;

        Singleton(const Singleton &other_) = delete;
        Singleton &operator=(const Singleton &other_) = delete;

        Singleton(const Singleton &&other_) = delete;
        Singleton &operator=(const Singleton &&other_) = delete;

    private:
        static void Cleanup();
        static std::mutex m_mutex;
        static std::atomic<T *> m_instance;
        static std::atomic<bool> m_is_cleanup;
    }; // Singleton


    template <typename T>
    std::mutex Singleton<T>::m_mutex;

    template <typename T>
    std::atomic<T *> Singleton<T>::m_instance(nullptr);

    template <typename T>
    std::atomic<bool> Singleton<T>::m_is_cleanup(false);

    template <typename T>
    T *Singleton<T>::GetInstance()
    {
        T *tmp = m_instance.load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire);

        if (nullptr == tmp)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            tmp = m_instance.load(std::memory_order_relaxed);
            if (nullptr == tmp && false == m_is_cleanup)
            {
                tmp = new T;
                std::atomic_thread_fence(std::memory_order_release);
                m_instance.store(tmp, std::memory_order_relaxed);
	
                std::atexit(Cleanup);
            }
        }
        return tmp;
    }

    template <typename T>
    void Singleton<T>::Cleanup()
    {
        m_is_cleanup = true;
        delete m_instance.load(std::memory_order_relaxed); 
        m_instance.store(nullptr, std::memory_order_relaxed);
    }

#endif // SINGLETON_HPP

