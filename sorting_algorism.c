#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "sorting_algorism.h"
#include "schedule.h"

void swap(void *p, void *q, size_t size){

    void *r = malloc(size);
    memcpy(r, p, size);
    memcpy(p, q, size);
    memcpy(q, r, size);
    free(r);

}

void selection_sort(void *base, size_t num, size_t size, int (*compar)(const void*, const void*)) {
    
    //從list的開頭往後讀，把讀到最小的資料放到最前面，再重下一個位置開始讀
    int i = 0, j = 0;
    for(i = 0; i < num; i++ ){
        for (j = i + 1 ; j < num ;j++){
            if((*compar)((base + (i * size)), (base + (j * size))) > 0)
                swap((base + (i * size)), (base + (j * size)), size);
        }
    }
}

void bubble_sort(void *base, size_t num, size_t size, int (*compar)(const void*, const void*)){

    //從右往左一次檢查兩個數字，如果右邊的數字較小就替換到左邊
    for (int wall = 0; wall < num; wall++){
        for (int i = (num - 1); i > wall; i--){
            if ((*compar)((base + (i * size)), (base + ((i - 1) * size))) < 0)
                swap((base + (i * size)), (base + ((i-1) * size)), size);
        }
    }
}

void insertion_sort(void *base, size_t num, size_t size, int (*compar)(const void*, const void*)){

    //把資料從牆右側的第一個數字抓到左側排列好的序列中，插入正確大小的位置
    for (int wall = 1; wall < num; wall++){
        for (int i = wall; i > 0; i--){
            if ((*compar)((base + (i * size)), (base + ((i - 1) * size))) < 0)
                swap((base + (i * size)), (base + ((i - 1) * size)), size);
            else
                break;
        }
    }
}

//=====================heap sort============================

/*
*Turn root subtree to max heap, and then turn its children subtree to max heap
*base: data array
*root: index of parent + 1
*node_len: length must be heapified
*size: size of the data in base
*compar: comparing function
*/
void max_heapify(void *base, int root, size_t node_len, size_t size, int (*compar)(const void*, const void*)){

    int left_index = root * 2;
    int right_index = root * 2 + 1;
    int max_index;

    //if left children's index is in range then compare root with left children
    if ((left_index <= node_len) && (*compar)((base + ((root - 1) * size)), (base + ((left_index - 1) * size))) < 0){
        max_index = left_index;
    } else{
        max_index = root;
    }

    //compare max with right children
    if ((right_index <= node_len) && (*compar)((base + ((max_index - 1) * size)), (base + ((right_index - 1) * size))) < 0){
        max_index = right_index;
    }

    printf("ROOT: %d, LEFT: %d, RIGHT: %d, MAX_INDEX: %d \n", root, left_index, right_index, max_index);
    if (max_index != root) {
        swap(base + (root - 1) * size, base + (max_index - 1) * size, size);
        max_heapify(base, max_index, node_len, size, compar);  //continue to heapify swapped children
    }
 
}

/*
*Sort data into a fully max heapify tree
*base: data array
*node_len: length must be heapified
*size: size of the data in base
*compar: comparing function
*/
void build_max_heap(void *base, size_t node_len, size_t size, int (*compar)(const void*, const void*)){

    for(int i = node_len / 2; i > 0; i--){
        printf("i: %d ", i);
        max_heapify(base, i, node_len, size, compar);
    }

}

/*
*Sorting. turn base to a max heapify tree -> swap base[0] and base[node_len - 1] -> heapify base[0]
*base: data array
*num: length of base
*size: size of the data in base
*compar: comparing function
*/
void heap_sort(void *base, size_t num, size_t size, int (*compar)(const void*, const void*)){

    size_t node_len = num;
    build_max_heap(base, node_len, size, compar);

    printf("\n=====SORTING=====\n");
    for(; node_len > 1;){
        swap(base, (base + (node_len - 1) * size), size);
        node_len--;
        max_heapify(base, 1, node_len, size, compar);
    }
}

//=====================merge sort============================

/*
*Merge two parts of array(base) to sorted one
*base: data array
*front: index of the beginning of the array
*mid: index of the middle of the array
*end: index of the end of the array
*size: size of the data in base
*compar: comparing function
*/
void merge(void *base, size_t front, size_t mid, size_t end, size_t size, int (*compar)(const void*, const void*)){

    int left_size = mid - front + 1;
    int right_size = end - mid;

    void *left = malloc(left_size * size);  //用於比較的左arr
    void *right = malloc(right_size * size);    //用於比較的右arr
    memcpy(left, base + front * size, left_size * size);
    memcpy(right, base + (mid + 1) * size, right_size * size);

    //比較左右arr的第一個值
    int i = 0, j = 0;   //左右arr比較的位置
    for (;(i < left_size && j < right_size);){
        if((*compar)((left + (i * size)), (right + (j * size))) < 0){
            memcpy((base + (front + i + j) * size), left + (i * size), size);
            i++;
        } else{
            memcpy((base + (front + i + j) * size), right + (j * size), size);
            j++;
        }
        printf("i: %d, j: %d\n", i, j);
        printf("%d %d %d\n", (base + (front + i + j) * size), (left + (i * size)), (right + (j * size)));
    }

    //沒比較完的塞回base中
    if (i == left_size){
        memcpy((base + (front + i + j) * size), right + (j * size), (right_size - j) * size);
    } else{
        memcpy((base + (front + i + j) * size), left + (i * size), (left_size - i) * size);
    }

    free(left);
    free(right);

}

/*
*Function used for recursion. Divide an array into two parts and then sort them separately
*base: data array
*front: index of the beginning of the array
*end: index of the end of the array
*size: size of the data in base
*compar: comparing function
*/
void sort(void *base, size_t front, size_t end, size_t size, int (*compar)(const void*, const void*)){

    //只剩一個元素時停止recursion
    //多於一個元素時分成左右兩半
    if (front < end){
        int mid = (front + end) / 2;
        sort(base, front, mid, size, compar);
        sort(base, (mid + 1), end, size, compar);
        merge(base, front, mid, end, size, compar);
        //printf("%d SORTED\n", front);
    }

}

/*
*Sorting
*base: data array
*num: length of base
*size: size of the data in base
*compar: comparing function
*/
void merge_sort(void *base, size_t num, size_t size, int (*compar)(const void*, const void*)){

    sort(base, 0, num - 1, size, compar);
    printf("FINISHED\n");

}