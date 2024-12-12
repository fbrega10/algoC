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


void upo_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    unsigned char * ptr = (unsigned char *) base;
    for (size_t i = 1; i < n; ++i)
    {
        size_t j = i;
        while (j > 0 && cmp(ptr + j * size, ptr + (j-1) * size) < 0)
        {
            upo_swap(ptr + j * size, ptr + (j-1) * size, size);
            j--; 
        }
    }
}

void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    if(n <= 1)
        return;  

    size_t left_size = n/2;   

    size_t righ_size = n-left_size;

    upo_merge_sort((char*)base, left_size, size, cmp);
    upo_merge_sort((char*)base + left_size * size, righ_size, size, cmp);
    upo_merge((char*)base, left_size, righ_size, size, cmp);
}

void upo_merge(void *base, size_t left_size, size_t righ_size, size_t size, upo_sort_comparator_t cmp){

    unsigned char * aux_array = malloc(size*(left_size + righ_size));

    unsigned char * aux_ptr = aux_array;

    unsigned char * basePtr = (unsigned char*) base;

    unsigned char * i1 = basePtr;
    unsigned char * i2 = basePtr + size * left_size;


    while((i1 != basePtr + size*left_size) && (i2 != basePtr + size*(left_size+righ_size)))
    {
        if (cmp(i1, i2) < 0) {    
            memcpy(aux_ptr, i1, size);
            aux_ptr += size;
            i1 += size;
        } else {
            memcpy(aux_ptr, i2, size);
            aux_ptr += size;
            i2 += size;
        }
    }

    while(i1 != basePtr + size*left_size)
    {
        memcpy(aux_ptr, i1, size);
        aux_ptr += size;
        i1 += size;
    }
    while(i2 != basePtr + size*(left_size+righ_size))
    {
        memcpy(aux_ptr, i2, size);
        aux_ptr += size;
        i2 += size;
    }
    memcpy(basePtr, aux_array, size*(left_size+righ_size));
    free(aux_array);
}





void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
}
