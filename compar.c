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

int compar_schedule_reverse(const void *p1, const void *p2) {

    if (compar_schedule(p1, p2) <= 0) {
        return 1;
    } else{
        return -1;
    }
}

int compar_sche(const void *p1, const void *p2) {

    //p1較大回傳正值,p2較大回傳負值    
    const struct schedule *a = p1;
    const struct schedule *b = p2; 


    if ((a -> begin_date) != (b -> begin_date)){
        return(a -> begin_date - b -> begin_date);
    }
    if ((a -> level - b -> level) != 0){
        return (a -> level - b -> level);
    }
    return ((b -> remuneration) - (a -> remuneration));

}

int compar_remuneration(const void *p1, const void *p2) {

    //p1較大回傳正值,p2較大回傳負值    
    const struct schedule **a = p1;
    const struct schedule **b = p2; 

    return (((*b) -> remuneration) - ((*a) -> remuneration));

}

int compar_begin_date(const void *p1, const void *p2) {

    //p1較大回傳正值,p2較大回傳負值    
    const struct schedule **a = p1;
    const struct schedule **b = p2; 

    return((*a) -> begin_date - (*b) -> begin_date);

}