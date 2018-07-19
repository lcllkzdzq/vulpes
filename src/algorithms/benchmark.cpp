//
//  benchmark.cpp
//  vulpes
//
//  Created by lcl on 2018/7/19.
//  Copyright © 2018 lcl. All rights reserved.
//

#include "benchmark.hpp"

#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

namespace vulpes {
    namespace benchmark {
        string now() {
            chrono::system_clock::time_point point = chrono::system_clock::now();
            time_t time = chrono::system_clock::to_time_t(point);
            tm *ptm = localtime(&time);
            
            chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(point.time_since_epoch());
            
            stringstream stream;
            stream << put_time(ptm, "%F %X") << "." << ms.count() % 1000;
            
            return stream.str();
        }
    }
}
