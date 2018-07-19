//
//  task.cpp
//  vulpes
//
//  Created by lcl on 2018/7/19.
//  Copyright © 2018 lcl. All rights reserved.
//

#include "task.hpp"

namespace vuples {
    task::task() : _impl(nullptr) {
        
    }
    
    task::task(void (*impl)()) : _impl(impl) {
        
    }
    
    task::~task() {
        
    }
    
    void task::run() {
        if (_impl) {
            _impl();
        }
    }
}
