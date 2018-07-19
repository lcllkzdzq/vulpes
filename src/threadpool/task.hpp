//
//  task.hpp
//  vulpes
//
//  Created by lcl on 2018/7/19.
//  Copyright © 2018 lcl. All rights reserved.
//

namespace vuples {
    class task {
    private:
        void (*_impl)();
    public:
        task();
        task(void (*impl)());
        ~task();
        
        void run();
    };
}
