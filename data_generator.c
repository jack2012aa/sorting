#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "schedule.h"
#include "compar.h"
#include "sorting_algorism.h"
#include "dataio.h"

int generate_int(int smallest, int largest){

    int num = (rand() % (largest - smallest) + smallest);
    return num;

}

void write_generated_data(FILE *fp, int len){

    for (int i = 0; i < len; i++)
        fprintf(fp, "%d %c %d\n", generate_int(0, 12), (rand() % 4 + 65), generate_int(3000, 30000));
    
}

void generate_dataset(char* file_name, int len, int size){
    
    //Generate dataset with length len
    struct schedule sche[len];
    read_data(file_name, sche, len);
    struct schedule *scheptr[len];
    for (int i = 0; i < len; i++){
        scheptr[i] = sche + i;
    }

    //Random dataset
    char result_name[50];
    sprintf(result_name, "random_data_%d.txt", len);
    write_result(result_name, scheptr, len);

    //Decreasing-ordered dataset
    sprintf(result_name, "decreasing_ordered_data_%d.txt", len);
    qsort(scheptr, len, size, compar_schedule_reverse);
    write_result(result_name, scheptr, len);

    //Increasing-ordered dataset
    sprintf(result_name, "increasing_ordered_data_%d.txt", len);
    qsort(scheptr, len, size, compar_schedule);
    write_result(result_name, scheptr, len);

    //Semi-ordered dataset
    sprintf(result_name, "semi-ordered_data_%d.txt", len);
    for (int i = 0; i < len / 4; i++){
        int l = generate_int(0, len - 1);
        int r = generate_int(0, len - 1);
        swap(scheptr + l, scheptr + r, size);
    }
    write_result(result_name, scheptr, len);

}

int main(){

    srand(time(NULL));

    
    //Generate full random dataset 'random_data_10000.txt'
    FILE *fp;
    fp = fopen("random_data_100000.txt", "w");
    write_generated_data(fp, 100000);
    fclose(fp);

    int size = sizeof(struct schedule *);
    for (int len = 10; len <= 100000; len = len * 10) {
        generate_dataset("random_data_100000.txt", len, size);
    }
    printf("==========FINISHED==========\n");

    return 0;
}


