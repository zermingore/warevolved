/**
 * \file
 * \date Jun, 21 2017
 * \author Zermingore
 * \brief ThreadSafeQueue template definitions
 */

#ifndef STRUCTURES_THREAD_SAFE_QUEUE_HXX_
# define STRUCTURES_THREAD_SAFE_QUEUE_HXX_

# include <thread>

# include <structures/ThreadSafeQueue.hh>



template <typename T>
ThreadSafeQueue<T>::~ThreadSafeQueue()
{
  std::unique_lock<std::mutex> lock(_lock);
  while (!_queue.empty())
  {
    _queue.pop();
  }

  // not unlocking the mutex
}



template <typename T>
void ThreadSafeQueue<T>::push(const T& element)
{
  std::unique_lock<std::mutex> lock(_lock);
  _queue.push(element);
  lock.unlock();
  _cvNotEmpty.notify_one();
}



template <typename T>
void ThreadSafeQueue<T>::push(T&& element)
{
  std::unique_lock<std::mutex> lock(_lock);
  _queue.push(std::move(element));
  lock.unlock();
  _cvNotEmpty.notify_one();
}



template <typename T>
T ThreadSafeQueue<T>::pop()
{
  std::unique_lock<std::mutex> lock(_lock);
  while (_queue.empty())
  {
    _cvNotEmpty.wait(lock);
  }

  auto element(_queue.front());
  _queue.pop();

  return element;
}



template <typename T>
void ThreadSafeQueue<T>::pop(T& element)
{
  std::unique_lock<std::mutex> lock(_lock);
  while (_queue.empty())
  {
    _cvNotEmpty.wait(lock);
  }

  element = _queue.front();
  _queue.pop();
}



template <typename T>
bool ThreadSafeQueue<T>::empty() const
{
  return _queue.empty();
}

#endif // STRUCTURES_THREAD_SAFE_QUEUE_HXX_
