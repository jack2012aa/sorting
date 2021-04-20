#include "schedule.h"
#include <stdio.h>

int compar_schedule(const void *p1, const void *p2) {

    //p1較大回傳正值,p2較大回傳負值    
    const struct schedule **a = p1;
    const struct schedule **b = p2; 


    if (((*a) -> begin_date) != ((*b) -> begin_date)){
        return((*a) -> begin_date - (*b) -> begin_date);
    }
    if (((*a) -> level - (*b) -> level) != 0){
        return ((*a) -> level - (*b) -> level);
    }
    return (((*b) -> remuneration) - ((*a) -> remuneration));

}