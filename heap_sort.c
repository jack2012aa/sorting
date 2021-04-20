#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"
#include "dataio.h"
#include "compar.h"

void swap(void *p, void *q, size_t size){

    void *r = malloc(size);
    memcpy(r, p, size);
    memcpy(p, q, size);
    memcpy(q, r, size);
    free(r);

}

/*
*turn root subtree to max heap, and then turn its children subtree to max heap
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
*sort data into a fully max heapify tree
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
*sorting. turn base to a max heapify tree -> swap base[0] and base[node_len - 1] -> heapify base[0]
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

int main(){

    struct schedule sche[30];
    read_data(sche, 30);

    struct schedule *scheptr[30];
    for (int i = 0; i < 30; i++){
        scheptr[i] = sche + i;
    }

    heap_sort(scheptr, 30, sizeof(struct schedule *), compar_schedule);

    write_result(scheptr, 30);

    return 0;
}