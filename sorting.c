#include "compar.h"
#include "dataio.h"
#include "sorting_algorism.h"
#include "schedule.h"
#include <stdio.h>



int main(){
    
    int data_len = 30;
    int size = sizeof(struct schedule *);

    struct schedule sche[data_len];
    read_data(sche, data_len);

    struct schedule *scheptr[data_len];
    for (int i = 0; i < data_len; i++){
        scheptr[i] = sche + i;
    }

    qsort(scheptr, data_len, size, compar_schedule);

    write_result(scheptr, data_len);

    return 0;
}