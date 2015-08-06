#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_

#include <iostream>
#include <functional>
#include <future>
#include <utility>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <queue>


class ThreadPool
{
public:
	ThreadPool() = delete;
	ThreadPool(int num_thread);

	template<class Function, class... Args>
	auto Enqueue(Function&& function, Args&&... args) ->
		std::future<typename std::result_of<Function(Args...)>::type>;
	
	~ThreadPool();
	
private:

	std::vector<std::thread> m_workThreads;
	std::queue<std::function<void()>> m_tasks;
	bool m_stop;

		//sync
	std::mutex m_queue_mutex;
	std::condition_variable m_condition;
	
};





#endif
