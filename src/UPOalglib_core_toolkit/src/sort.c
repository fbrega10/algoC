/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include "sort_private.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/utility.h>


void upo_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    if (base != NULL){
        unsigned char * ptr = base;

        for (size_t i = 1; i < n ; ++i){
            size_t j = i;
            while (j > 0 && cmp(ptr + j * size, ptr + (j-1) * size) < 0){
                upo_swap(ptr + j * size, ptr + (j-1) * size, size);
                --j;
            }
        }
    }
}

void upo_merge(void *base, size_t left, size_t mid, size_t right, size_t size, upo_sort_comparator_t cmp)
{
    size_t i = left;
    size_t j = mid + 1;
    size_t k = 0;

    unsigned char * ptr = base;
    unsigned char * cpy = malloc(size * (right - left + 1));

    if (cpy == NULL)
        perror("\ncould not allocate memory \n");

    while (i <= mid && j <= right){

        int result = cmp(ptr + i * size, ptr + j * size);

        if (result <= 0){
            memcpy(cpy + k * size, ptr + i * size, size);
            ++i;
            ++k;
        }
        else{
            memcpy(cpy + k * size, ptr + j * size, size);
            ++j;
            ++k;
        }
    }
    while (i <= mid){
            memcpy(cpy + k * size, ptr + i * size, size);
            ++i;
            ++k;
    }
    while (j <= right){
            memcpy(cpy + k * size, ptr + j * size, size);
            ++j;
            ++k;
    }
    memcpy(ptr + left * size , cpy, size * (right - left + 1));
    free(cpy);
}


void upo_merge_sort_rec(void *base, size_t left, size_t right, size_t size, upo_sort_comparator_t cmp)
{
    if (left >= right)
        return;
    size_t mid = (left + right) / 2;
    upo_merge_sort_rec(base, left, mid, size, cmp);
    upo_merge_sort_rec(base, mid + 1, right, size, cmp);
    upo_merge(base, left, mid, right, size, cmp);
}

void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    if (base != NULL)
        upo_merge_sort_rec(base, 0, n - 1, size, cmp);
}

size_t upo_partition(void *base, size_t left, size_t right, size_t size, upo_sort_comparator_t cmp){
    size_t p = left;
    size_t i = left + 1;
    size_t j = right;
    unsigned char * ptr = base;
    while(1){
        while (i < right && cmp(ptr + i * size, ptr + p * size) < 0)
            ++i;

        while (j > left && cmp(ptr + j * size, ptr + p * size) > 0)
            --j;

        if (i >= j)
            break;

        upo_swap(ptr + i * size, ptr + j * size, size);
    }
    upo_swap(ptr + p * size, ptr + j * size, size);
    return j;
}

void upo_quick_sort_rec(void *base, size_t left, size_t right, size_t size, upo_sort_comparator_t cmp)
{
    if (left >= right)
        return;

    size_t j = upo_partition(base, left, right, size, cmp);
    if (j > left)
        upo_quick_sort_rec(base, left, j - 1, size, cmp);
    upo_quick_sort_rec(base, j + 1, right, size, cmp);
}
void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    if (base != NULL)
        upo_quick_sort_rec(base, 0, n - 1, size, cmp);
}
