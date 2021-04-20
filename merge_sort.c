#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"
#include "dataio.h"
#include "compar.h"

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

void merge_sort(void *base, size_t num, size_t size, int (*compar)(const void*, const void*)){

    sort(base, 0, num - 1, size, compar);
    printf("FINISHED\n");

}

int main(){

    struct schedule sche[30];
    read_data(sche, 30);

    struct schedule *scheptr[30];
    for (int i = 0; i < 30; i++){
        scheptr[i] = sche + i;
    }

    merge_sort(scheptr, 30, sizeof(struct schedule *), compar_schedule);

    write_result(scheptr, 30);

    return 0;
}