#include "task.hpp"

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
        vector<thread> threads;
        static void work_thread(threadpool* pool);
        void join_all();
    };
}
