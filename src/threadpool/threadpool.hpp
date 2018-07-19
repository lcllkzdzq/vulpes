//
//  threadpool.hpp
//  vulpes
//
//  Created by lcl on 2018/7/19.
//  Copyright © 2018 lcl. All rights reserved.
//

#include "task.hpp"
#include "sync_queue.hpp"

#include <vector>
#include <thread>

using namespace std;

namespace vuples {
    class threadpool {
    public:
        threadpool(unsigned const thread_count = 1);
        ~threadpool();
        
        void add_task(vuples::task& task);
    private:
        vector<thread> _threads;
        sync_queue<vuples::task> _work_queue;
        
        static void work_thread(threadpool* pool);
        void enqueue(vuples::task& task);
        void close();
        void join();

    };
}
