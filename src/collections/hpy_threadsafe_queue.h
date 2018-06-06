#ifndef HPY_COLLECTIONS_HPY_THREADSAFE_QUEUE_
#define HPY_COLLECTIONS_HPY_THREADSAFE_QUEUE_

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

/*
this is a thread safe queue, just for two threads. 
One is producer, and the other is consumer.
*/

template <typename T>
class ThreadsafeQueue
{
public:
    ThreadsafeQueue() = default;
    //还没有确定该不该用引用
    void PushRight(const T& data);
    const T& PopLeft();
    int Size();
    
private:
    std::mutex mux_;
    std::condition_variable cond_;
    std::queue<T> queue_;

};
#endif
