#include "threadpool.hpp"


namespace vuples {
    threadpool::threadpool(unsigned const thread_count) {
        threads.reserve(thread_count);
        for (int i = 0; i < thread_count; ++i) {
            thread td(threadpool::work_thread, this);
            threads.push_back(move(td));
        }
    }

    threadpool::~threadpool() {
        
        join_all();
    }

    void threadpool::add_task(vuples::task& task) {

    }
    
    void threadpool::work_thread(threadpool* pool) {
        
    }
    
    void threadpool::join_all() {
    }
}
