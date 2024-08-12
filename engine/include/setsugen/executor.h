#pragma once

#include <setsugen/pch.h>

#include <future>
#include <memory>
#include <thread>
#include <type_traits>
#include "setsugen/exception.h"

namespace setsugen
{

/**
 * @brief Executors class
 * Call static method `create` to create an instance of the executor.
 * Supported executors are FixedThreadPoolExecutor, SingleThreadExecutor, and CachedThreadPoolExecutor.
 *  - FixedThreadPoolExecutor: A fixed-size thread pool executor.
 *  - SingleThreadExecutor: A single thread executor. It executes tasks in a single thread.
 *  - CachedThreadPoolExecutor: A thread pool executor that creates new threads as needed, but will reuse previously
 * constructed threads when they are available.
 *
 * @tparam ExecutorTarget
 */
template<class ExecutorTarget>
class Executor
{
public:
  using ExecutorTask = std::function<void(bool)>;

  virtual ~Executor() = default;

  template<typename F, typename... Args>
    requires std::is_invocable_v<F, Args...>
  auto submit(F&& func, Args&&... args)
  {
    using ReturnType = std::invoke_result_t<F, Args...>;

    std::function<ReturnType()> binder = std::bind(std::forward<F>(func), std::forward<Args>(args)...);

    auto ptask = std::make_shared<std::packaged_task<ReturnType(bool)>>(
        [binder](auto stopped)
        {
          if (stopped)
          {
            throw InvalidStateException{"Executor is stopped"};
          }

          return binder();
        });

    auto future = ptask->get_future();

    enqueue([ptask](bool stopped) { (*ptask)(stopped); });

    return future;
  }

  template<typename... Args>
  static std::unique_ptr<ExecutorTarget> create(Args&&... args)
  {
    return std::make_unique<ExecutorTarget>(std::forward<Args>(args)...);
  }

  /**
   * @brief Start the executor.
   * This method can be called anywhere in the code. It will start the executor and execute the tasks in the queue.
   * If the executor is already started, this method will do nothing.
   */
  virtual void start() = 0;

  /**
   * @brief Stop the executor.
   * This method can be called anywhere in the code. It will trigger the executor to stop executing tasks.
   * If there are tasks are being executed, the executor will wait until all tasks are completed then stop.
   * If there are tasks in the queue, executor will throw an exception to their futures.
   * If the executor is already stopped, this method will do nothing.
   */
  virtual void stop() = 0;

  /**
   * @brief Force stop the executor.
   * This method can be called anywhere in the code. It will trigger the executor to stop executing tasks.
   * If there are tasks are being executed, their future may cause infinite waiting due to the force stop.
   * If there are tasks in the queue, executor will throw an exception to their futures.
   * If the executor is already stopped, this method will do nothing.
   */
  virtual void force_stop() = 0;

  /**
   * @brief Join the executor.
   * This method can be called anywhere in the code. It will wait until all tasks are completed then stop.
   * If the executor is already stopped, this method will do nothing.
   */
  virtual void join() = 0;

  /**
   * @brief Check if the executor is stopped.
   * This method can be called anywhere in the code. It will return true if the executor is stopped.
   * Otherwise, it will return false.
   */
  virtual bool is_stopped() const = 0;

  /**
   * @brief Check if the queue is empty.
   * This method can be called anywhere in the code. It will return true if the queue is empty.
   * Otherwise, it will return false.
   */
  virtual bool is_queue_empty() const = 0;

protected:
  virtual void         enqueue(ExecutorTask&& task) = 0;
  virtual ExecutorTask dequeue()                    = 0;
};

class FixedThreadPoolExecutor : public Executor<FixedThreadPoolExecutor>
{
public:
  explicit FixedThreadPoolExecutor(size_t num_threads = 0);
  ~        FixedThreadPoolExecutor() override;

  void start() override;
  void stop() override;
  void force_stop() override;
  void join() override;
  bool is_stopped() const override;
  bool is_queue_empty() const override;

protected:
  void         enqueue(ExecutorTask&& task) override;
  ExecutorTask dequeue() override;

private:
  std::vector<std::unique_ptr<std::thread>> m_threads;
  std::queue<ExecutorTask>                  m_tasks;
  mutable std::mutex                        m_queue_mutex;
  std::atomic<bool>                         m_stopped;
  int                                       m_num_threads;
};

class SingleThreadExecutor : public Executor<SingleThreadExecutor>
{
public:
   SingleThreadExecutor();
  ~SingleThreadExecutor() override;

  void start() override;
  void stop() override;
  void force_stop() override;
  void join() override;
  bool is_stopped() const override;
  bool is_queue_empty() const override;

protected:
  void         enqueue(ExecutorTask&& task) override;
  ExecutorTask dequeue() override;

private:
  std::unique_ptr<std::thread> m_thread;
  std::queue<ExecutorTask>     m_tasks;
  bool                         m_stopped;
};

class CachedThreadPoolExecutor : public Executor<CachedThreadPoolExecutor>
{
public:
   CachedThreadPoolExecutor();
  ~CachedThreadPoolExecutor();

private:
  std::vector<std::unique_ptr<std::thread>> m_threads;
  std::queue<ExecutorTask>                  m_tasks;
  std::mutex                                m_queue_mutex;
};

} // namespace setsugen
