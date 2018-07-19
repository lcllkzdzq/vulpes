//
//  random.hpp
//  vulpes
//
//  Created by lcl on 2018/7/19.
//  Copyright © 2018 lcl. All rights reserved.
//

#ifndef random_hpp
#define random_hpp

#include <random>

using namespace std;

namespace vuples {
    template <typename T>
    T random(T min, T max) {
        random_device rd;
        default_random_engine e(rd());
        uniform_int_distribution<T> dis(min, max);
        
        return dis(e);
    }
    
    template<typename T, template <typename...> class Container>
    Container<T> random_pool(T min, T max, int count) {
        random_device rd;
        default_random_engine e(rd());
        uniform_int_distribution<T> dis(min, max);
        
        Container<T> container;
        container.reserve(count);
        for (int i = 0; i < count; ++i) {
            container.push_back(dis(e));
        }
        
        return move(container);
    }
}

#endif /* random_hpp */
