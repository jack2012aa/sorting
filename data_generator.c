#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "schedule.h"

int generate_int(int smallest, int largest);
void write_generated_data(FILE *fp, int len);

int main(){

    srand(time(NULL));

    FILE *fp;
    fp = fopen("data.txt", "w");
    write_generated_data(fp, 30);
    fclose(fp);

    fclose(fdata);

    return 0;
}

int generate_int(int smallest, int largest){

    int num = (rand() % (largest - smallest) + smallest);
    return num;

}

void write_generated_data(FILE *fp, int len){

    for (int i = 0; i < len; i++)
        fprintf(fp, "%d %c %d\n", generate_int(0, 12), (rand() % 4 + 65), generate_int(3000, 30000));
    
}
