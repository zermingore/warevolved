/**
 * \file
 * \date Jun, 21 2017
 * \author Zermingore
 * \brief ThreadSafeQueue class declaration
 */

#ifndef STRUCTURES_THREAD_SAFE_QUEUE_HH_
# define STRUCTURES_THREAD_SAFE_QUEUE_HH_

# include <queue>
# include <mutex>
# include <condition_variable>

/**
 * \class ThreadSafeQueue
 * \brief Thread safe queue, wrapper over the std::queue
 */
template<typename T>
class ThreadSafeQueue
{
public:
  /**
   * \brief Default constructor
   */
  ThreadSafeQueue() = default;

  /**
   * \brief Destructor. Empty the queue
   */
  ~ThreadSafeQueue();

  /**
   * \brief Deleted copy constructor
   */
  ThreadSafeQueue(const ThreadSafeQueue& queue) = delete;

  /**
   * \brief Deleted assignment operator
   */
  ThreadSafeQueue& operator=(const ThreadSafeQueue& queue) = delete;


  /**
   * \brief Push the given element to the queue
   * \param element Element to push into the queue
   */
  void push(const T& element);

  /**
   * \brief Move the given element into the queue
   * \param element Element to move into the queue
   */
  void push(T&& element);


  /**
   * \brief Pop the first element of the queue
   * \return Poped element
   * \note Basic exception safety guarantee
   * \note Blocks if the queue is empty
   */
  T pop();

  /**
   * \brief Pop the first element
   * \param element Returned front element
   * \note Strong exception safety guarantee
   * \note Blocks if the queue is empty
   */
  void pop(T& element);


  /**
   * \brief Check if the queue is empty
   * \return true if the queue is empty
   */
  bool empty() const;


private:
  std::queue<T> _queue;                  ///< std queue containing the elements
  std::mutex _lock;                      ///< lock the queue while written
  std::condition_variable _cv_not_empty; ///< prevent pop when empty
};


# include <structures/ThreadSafeQueue.hxx>

#endif /* !STRUCTURES_THREAD_SAFE_QUEUE_HH_ */
