//
//  threadpool.cpp
//  vulpes
//
//  Created by lcl on 2018/7/19.
//  Copyright © 2018 lcl. All rights reserved.
//

#include "threadpool.hpp"


namespace vuples {
    threadpool::threadpool(unsigned const thread_count) {
        _threads.reserve(thread_count);
        for (int i = 0; i < thread_count; ++i) {
            thread td(threadpool::work_thread, this);
            _threads.push_back(move(td));
        }
    }

    threadpool::~threadpool() {
        close();
        join();
    }

    void threadpool::add_task(vuples::task& task) {
        enqueue(task);
    }
    
    void threadpool::work_thread(threadpool* pool) {
        for (;;) {
            task task;
            vuples::sync_status st = pool->_work_queue.wait_dequeue(task);
            if (st == vuples::sync_status::closed) {
                return;
            }
            
            task.run();
        }
    }
    
    void threadpool::enqueue(vuples::task& task) {
        _work_queue.enqueue(move(task));
    }
    
    void threadpool::close() {
        _work_queue.close();
    }
    
    void threadpool::join() {
        for (int i = 0; i < _threads.size(); ++i) {
            _threads[i].join();
        }
    }
}
