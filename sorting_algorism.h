#include <stddef.h>
#ifndef SORTING_ALGORISM_H
#define SORTING_ALGORISM_H

void selection_sort(void *base, size_t num, size_t size, int (*compar)(const void*, const void*));
void bubble_sort(void *base, size_t num, size_t size, int (*compar)(const void*, const void*));
void insertion_sort(void *base, size_t num, size_t size, int (*compar)(const void*, const void*));

#endif