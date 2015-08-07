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


//NOTE: function with trailing return type declared with "auto" type specifier
template<class Function, class... Args>
auto ThreadPool::Enqueue(Function&& function, Args&&... args) ->
	std::future<typename std::result_of<Function(Args...)>::type>
{
		//NOTE： class result_of<F(ArgTypes...)> ; 在编译时推断出函数调用的返回类型
		using returnType = typename std::result_of<Function(Args...)>::type;
		//typedef (typename std::result_of<Function(Args...)>::type) returnType;

		//NOTE： make_shard ==> shared_ptr
		//packaged_task ==> 包装任何的可调用目标（function，lamda， bind expression etc）， 这样可以
		//异步地调用。 它的返回值和抛出的异常存在一个shared object中， 这个shared object可以通过std::future对象访问。
	auto task = std::make_shared<std::packaged_task<returnType()>>(
		std::bind(std::forward<Function>(function), std::forward<Args>(args)...)
	);
		
	std::future<returnType> res = task->get_future();
	{
		std::unique_lock<std::mutex> lock(this->m_queue_mutex); //生命周期结束时，释放锁

		if (this->m_stop) {
			throw std::runtime_error("enqueue on stopped ThreadPool");
		}

		this->m_tasks.emplace([task]() { (*task)(); } );
	}

	this->m_condition.notify_one(); //发送信号给其它一个工作线程
	
	return res; //future, 在work线程中执行完这个task后， 可以用 res.get() 获取结果值
		
}




#endif
