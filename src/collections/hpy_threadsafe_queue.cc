#ifndef HPY_COLLECTIONS_HPY_THREADSAFE_QUEUE_
#include "collections/hpy_threadsafe_queue.h"
#endif

template <typename T>
void ThreadsafeQueue<T>::PushRight(const T& data)
{
    std::lock_guard<std::mutex> my_lock_guard(mux_);
    queue_.push_back(data);
    if (queue_.size() == 1)
        cond_.notify_one();
}

template <typename T>
const T& ThreadsafeQueue<T>::PopLeft()
{
    std::unique_lock<std::mutex> lock(mux_);
    while (queue_.empty() == true)
        cond_.wait(lock);
    const T& front  = queue_.front();
    queue_.pop_front();
    return front;
}

template <typename T>
int ThreadsafeQueue<T>::Size()
{
    std::lock_guard<std::mutex> my_lock_guard(mux_);
    return queue_.size();
}