#include "ThreadPool.hpp"



ThreadPool::ThreadPool(int num_thread) 
	: m_stop(false)
{
    for (int i = 0; i < num_thread; i++) {  
        m_workThreads.emplace_back(
            [this] //capture this, so we can access the member-var of ThreadPool in this lamda
            {
                for (;;) {
                    std::unique_lock<std::mutex> lk(this->m_queue_mutex);
                    this->m_condition.wait(lk, [this] {
                            return (this->m_stop || !this->m_tasks.empty()); }); //停止或者有task，就往下执行
                    if (this->m_stop) { //停止 ， 直接返回
                        return;
                    }

                    //取出tasks中的task执行
                    std::function<void()> task = std::move(this->m_tasks.front());
                    this->m_tasks.pop();

                    std::thread t(task);
                    t.detach();
                    //task();
					
                } //for
				
            } //body of lamda
                                   ); //emplace_back
		
    }
}



ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(m_queue_mutex);
        this->m_stop = true;
    }

    m_condition.notify_all();
    for (std::thread& work : this->m_workThreads) {
        if (work.joinable()) {
            work.join();
        }
    }
	
}
