#include <stdio.h>
#include <stdlib.h>
#include "dataio.h"
#include "schedule.h"

void read_data(char* file_name, struct schedule *sche, int len){

    FILE *fdata;
    fdata = fopen(file_name, "r");
    for (int i = 0; i < len; i++, sche++){
        fscanf(fdata, "%d %c %d", &(sche -> begin_date), &(sche -> level), &(sche -> remuneration));
        fgetc(fdata);   //change line
    }
    fclose(fdata);

}

void write_result(char* file_name, struct schedule **sche, int len){
    
    FILE *fresult;
    fresult = fopen(file_name, "w");
    for (int i = 0; i < len; i++, sche++)
        fprintf(fresult, "%d %c %d\n", (*sche) -> begin_date, (*sche) -> level, (*sche) -> remuneration);
    fclose(fresult);

}
