#include "compar.h"
#include "dataio.h"
#include "sorting_algorism.h"
#include "schedule.h"
#include <stdio.h>
#include <time.h>

const int ptr_size = sizeof(struct schedule *);
const int size = sizeof(struct schedule);

double test_sorting_algorism(void (*sort)(void*, size_t, size_t, int (*)(const void*, const void*)),
                            int (*compar)(const void*, const void*),
                            char* file_name, int len, int schwartzian){

    struct schedule sche[len];
    read_data(file_name, sche, len);
    clock_t start, end;
    if (schwartzian == 0) {
        start = clock();
        sort(sche, len, size, compar);
        end = clock();
    } else{
        struct schedule *scheptr[len];
        for (int i = 0; i < len; i++){
            scheptr[i] = sche + i;
        }
        start = clock();
        sort(scheptr, len, ptr_size, compar);
        end = clock();
    }

    double diff = end - start;
    
    return diff;
}

void test_time(void (*sort)(void*, size_t, size_t, int (*)(const void*, const void*))){
    printf("Different input size: \n");
    printf("10: %f\n", test_sorting_algorism(sort, compar_schedule, "random_data_10", 10, 1));
    printf("100: %f\n", test_sorting_algorism(sort, compar_schedule,"random_data_100", 100, 1));
    printf("1000: %f\n", test_sorting_algorism(sort, compar_schedule,"random_data_1000", 1000, 1));
    printf("10000: %f\n", test_sorting_algorism(sort, compar_schedule,"random_data_10000", 10000, 1));
    printf("100000: %f\n", test_sorting_algorism(sort, compar_schedule,"random_data_100000", 100000, 1));
    printf("\n");

    printf("Different input order: \n");
    printf("Increasing order: %f\n", test_sorting_algorism(sort, compar_schedule,"increasing_ordered_data_100000", 100000, 1));
    printf("Decreasing order: %f\n", test_sorting_algorism(sort, compar_schedule,"decreasing_ordered_data_100000", 100000, 1));
    printf("Semi-ordered: %f\n", test_sorting_algorism(sort, compar_schedule,"semi-ordered_data_100000", 100000, 1));
    printf("\n");

    printf("The size of value set: \n");
    printf("Small value set: %f\n", test_sorting_algorism(sort, compar_begin_date, "random_data_100000", 100000, 1));
    printf("Large value set: %f\n", test_sorting_algorism(sort, compar_remuneration, "random_data_100000", 100000, 1));
    printf("\n");

    printf("Complex/Simple data structure: \n");
    printf("Simple data structure: %f\n", test_sorting_algorism(sort, compar_begin_date, "random_data_100000", 100000, 1));
    printf("\n");

    printf("With/Without Schwartzian transform: \n");
    printf("Without transform: %f\n", test_sorting_algorism(sort, compar_sche,"random_data_100000", 100000, 0));
    printf("\n");
}

int main(){

    printf("===========Selection Sort===========\n");
    test_time(selection_sort);

    printf("===========Insertion Sort===========\n");
    test_time(insertion_sort);

    printf("===========Bubble Sort===========\n");
    test_time(bubble_sort);

    printf("===========Merge Sort===========\n");
    test_time(merge_sort);

    printf("===========Heap Sort===========\n");
    test_time(heap_sort);

    return 0;
}