#include <common/structures/ThreadSafeQueue.hh>

#include <thread>


template <typename T>
void ThreadSafeQueue<T>::push(const T& element)
{
  std::unique_lock<std::mutex> lock(_lock);
  _queue.push(element);
  lock.unlock();
  _cv_not_empty.notify_one();
}


template <typename T>
void ThreadSafeQueue<T>::push(T&& element)
{
  std::unique_lock<std::mutex> lock(_lock);
  _queue.push(std::move(element));
  lock.unlock();
  _cv_not_empty.notify_one();
}



template <typename T>
T ThreadSafeQueue<T>::pop()
{
  std::unique_lock<std::mutex> lock(_lock);
  while (_queue.empty())
  {
    _cv_not_empty.wait(lock);
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
    _cv_not_empty.wait(lock);
  }

  element = _queue.front();
  _queue.pop();
}
