//
//  algorithms.cpp
//  vulpes
//
//  Created by lcl on 2018/7/19.
//  Copyright © 2018 lcl. All rights reserved.
//

#include "algorithms.hpp"

namespace vulpes {
    namespace algorithms {
        // insert sort
        void insert_sort(vector<int>& array) {
            if (array.size() == 0) {
                return;
            }
            
            for (int i = 1; i < array.size(); ++i) {
                int n = array[i];
                
                int j = i - 1;
                while (j >= 0 && array[j] > n) {
                    array[j + 1] = array[j];
                    --j;
                }
                
                array[j + 1] = n;
            }
        }
        
        void select_sort(vector<int>& array) {
            
        }
        
        void bubble_sort(vector<int>& array) {
            
        }
        
        // merge sort
        void merge(std::vector<int>& array, std::vector<int>& left, std::vector<int>& right) {
            int li = 0;
            int ri = 0;
            int ai = 0;
            
            while (ai < array.size()) {
                if (li >= left.size()) {
                    array[ai++] = right[ri++];
                } else if (ri >= right.size()) {
                    array[ai++] = left[li++];
                } else if (left[li] < right[ri]) {
                    array[ai++] = left[li++];
                } else {
                    array[ai++] = right[ri++];
                }
            }
        }
        
        void merge_sort(vector<int>& array) {
            if (array.size() <= 1) {
                return;
            }
            
            int m = (int)array.size() / 2;
            std::vector<int> left(array.begin(), array.begin() + m);
            std::vector<int> right(array.begin() + m, array.end());
            
            merge_sort(left);
            merge_sort(right);
            merge(array, left, right);
        }
        
        void heap_sort(vector<int>& array) {
            
        }
    }
}
