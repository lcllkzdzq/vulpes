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
        
        // select sort
        void select_sort(vector<int>& array) {
            for (int i = 0; i < array.size(); ++i) {
                int n = array[i];
                int index = i;
                
                int j;
                for (j = i; j < array.size(); ++j) {
                    if (n > array[j]) {
                        n = array[j];
                        index = j;
                    }
                }
                
                if (index != i) {
                    array[index] = array[i];
                    array[i] = n;
                }
            }
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
        
        // heap sort
        void max_heapify(vector<int>& array, int index, int len) {
            int left = index << 1;
            int right = (index << 1) + 1;
            int largest = index;
            
            if (left < len) {
                largest = array[largest] >= array[left] ? largest : left;
            }
            
            if (right < len) {
                largest = array[largest] >= array[right] ? largest : right;
            }
            
            if (largest != index) {
                int temp = array[index];
                array[index] = array[largest];
                array[largest] = temp;
                max_heapify(array, largest, len);
            }
            
            //        int cur = index;
            //        while (cur < len) {
            //            int largest = cur;
            //            int left = index << 1;
            //            int right = (index << 1) + 1;
            //
            //            if (left < len) {
            //                largest = array[largest] >= array[left] ? largest : left;
            //            }
            //
            //            if (right < len) {
            //                largest = array[largest] >= array[right] ? largest : right;
            //            }
            //
            //            if (largest != cur) {
            //                int temp = array[index];
            //                array[index] = array[largest];
            //                array[largest] = temp;
            //                cur = largest;
            //            } else {
            //                break;
            //            }
            //        }
        }
        
        void build_max_heap(vector<int>& array) {
            for (int i = (int)array.size() / 2; i >= 0; --i) {
                max_heapify(array, i, (int)array.size());
            }
        }
        
        void heap_sort(vector<int>& array) {
            build_max_heap(array);
            
            for (int i = (int)array.size() - 1; i >= 1; --i) {
                int temp = array[i];
                array[i] = array[0];
                array[0] = temp;
                max_heapify(array, 0, i);
            }
        }
        
        // quick sort
        int partition(vector<int>& array, int start, int end) {
            int val = array[end - 1];
            int index = start;
            
            for (int i = start; i < end - 1; ++i) {
                if (array[i] < val) {
                    int temp = array[i];
                    array[i] = array[index];
                    array[index++] = temp;
                }
            }
            
            array[end - 1] = array[index];
            array[index] = val;
            
            return index;
        }
        
        void partition_sort(vector<int>& array, int start, int end) {
            if (end > start) {
                int index = partition(array, start, end);
                partition_sort(array, start, index);
                partition_sort(array, index + 1, end);
            }
        }
        
        
        void quick_sort(vector<int>& array) {
            partition_sort(array, 0, (int)array.size());
        }
    }
}
