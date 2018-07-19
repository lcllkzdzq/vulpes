//
//  algorithms.hpp
//  vulpes
//
//  Created by lcl on 2018/7/19.
//  Copyright © 2018 lcl. All rights reserved.
//

#ifndef algorithms_hpp
#define algorithms_hpp

#include <vector>

using namespace std;

namespace vulpes {
    namespace algorithms {
        void insert_sort(vector<int>& array);
        void select_sort(vector<int>& array);
        void bubble_sort(vector<int>& array);
        void merge_sort(vector<int>& array);
        void heap_sort(vector<int>& array);
        void quick_sort(vector<int>& array);
    }
}

#endif /* algorithms_hpp */
