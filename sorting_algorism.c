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