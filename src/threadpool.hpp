#include "task.hpp"

namespace vuples {
    class threadpool {
    public:
        threadpool(unsigned const thread_count = 1);
        ~threadpool();
        
        void add_task(vuples::task& task); 
    };
}
