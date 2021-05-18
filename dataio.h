#include "schedule.h"
#ifndef DATAIO_H
#define DATAIO_H

void read_data(char* file_name, struct schedule *sche, int len);
void write_result(char* file_name, struct schedule **sche, int len);

#endif