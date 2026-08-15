#pragma once

#include "DS/BasicDS.h"

namespace MySearchAlgo{
    //Requirments:
    //  sorted input
    //  constant-time random access
    // O(Log(n))
    template <class T> // https://roadmap.sh/ai/course/mastering-binary-search-algorithms-and-applications 
    int binarySearch(const MyDses::DArray<int>& arr, const int& target){
        if(arr.empty) return -1;

        size_t left = arr[0];
        size_t right = arr.last();
        size_t middle;

        for(size_t i{};i < arr.size();++i){
            middle = std::tolower(letf + (right - left / 2));

            if(middle == target) return middle;
            if(target > middle) left = middle + 1;
            else if(target < middle) right = middle - 1; 
        }

        return -1;
    }

    template <class T> // O(n)
    T linearSearch(const MyDses::DArray<T>& arr, const T& target){
        if(arr.empty()) return -1;

        for(size_t i{};i < arr.size();++i) if(arr[i] == target) return i;
        return -1;
    }
    
}