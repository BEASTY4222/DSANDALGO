#pragma once

#include "DS/BasicDS.h"

#include <cmath>

namespace MySortingAlgo{

/*
    Algorithm 	    Time Complexity 	                            Space Complexity
	                Best 	    Average 	        Worst 	        Worst
    Quicksort 	    Ω(n log(n)) 	Θ(n log(n)) 	O(n^2) 	        O(log(n))
    Mergesort 	    Ω(n log(n)) 	Θ(n log(n)) 	O(n log(n))     O(n)
    Timsort 	    Ω(n) 	        Θ(n log(n)) 	O(n log(n)) 	O(n)
    Heapsort 	    Ω(n log(n)) 	Θ(n log(n)) 	O(n log(n)) 	O(1)
    Bubble Sort     Ω(n) 	        Θ(n^2) 	        O(n^2) 	        O(1)
    Insertion Sort 	Ω(n) 	        Θ(n^2) 	        O(n^2) 	        O(1)
    Selection Sort 	Ω(n^2) 	        Θ(n^2) 	        O(n^2) 	        O(1)
    Tree Sort 	    Ω(n log(n)) 	Θ(n log(n)) 	O(n^2) 	        O(n)
    Shell Sort 	    Ω(n log(n)) 	Θ(n(log(n))^2) 	O(n(log(n))^2) 	O(1)
    Bucket Sort 	Ω(n+k) 	        Θ(n+k) 	        O(n^2) 	        O(n)
    Radix Sort 	    Ω(nk) 	        Θ(nk) 	        O(nk) 	        O(n+k)
    Counting Sort 	Ω(n+k) 	        Θ(n+k) 	        O(n+k) 	        O(k)
    Cubesort 	    Ω(n) 	        Θ(n log(n)) 	O(n log(n)) 	O(n)
*/
    void bubbleSort(MyDses::DArray<int>& arr){
        if (arr.size() < 2) return;

        int arrSize = arr.size();
        for(size_t i = 0;i < arrSize - 1;++i){
            bool swapped = false;
            for(size_t j = 0;j < arrSize - i - 1;++j){
                if(arr[j] > arr[j + 1]){
                    swapped = true;
                    std::swap(arr[j], arr[j + 1]);
                }
            }
            if(!swapped) return;
        }
    }

    MyDses::DArray<int> insertionSort(MyDses::DArray<int>& arr){
        for(int i = 1; i < arr.size(); i++) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return arr;
    }

    void selectionSort(){

    }

    void mergeSort(MyDses::DArray<int>& arr, int start, int end){
        if (end - start < 2) return;

        size_t middle = start + (end - start) / 2;;

        mergeSort(arr, start, middle);
        
        mergeSort(arr, middle, end);
        

        return merge(arr, start, middle, end);
    }

    void merge(MyDses::DArray<int>& arr ,size_t start, size_t mid, size_t end){
        MyDses::DArray<int> sortedArr(end - start);
        size_t i = start, j = mid;
        while(i < mid && j < end){
            if(arr[i] <= arr[j]){
                sortedArr.add_back(arr[i]);
                i++;
            }else{
                sortedArr.add_back(arr[j]);
                j++;
            }
        } 

        while (i < mid) {
            sortedArr.add_back(arr[i]);
            i++;
        }

        while (j < end) {
            sortedArr.add_back(arr[j]);
            j++;
        }
        
        for (size_t i = 0; i < sortedArr.size(); ++i) {
            arr[start + i] = sortedArr[i];
        }
    }

    void quickSort(){

    }

    void heapSort(){

    }
}