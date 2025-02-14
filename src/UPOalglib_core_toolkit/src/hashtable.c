/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 * \author Fabio Bregasi
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
#include "hashtable_private.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <upo/error.h>
#include <upo/utility.h>



upo_ht_sepchain_t upo_ht_sepchain_create(size_t m, upo_ht_hasher_t key_hash, upo_ht_comparator_t key_cmp)
{
    upo_ht_sepchain_t ht = NULL;
    size_t i = 0;

    /* preconditions */
    assert( key_hash != NULL );
    assert( key_cmp != NULL );

    /* Allocate memory for the hash table type */
    ht = malloc(sizeof(struct upo_ht_sepchain_s));
    if (ht == NULL)
    {
        perror("Unable to allocate memory for Hash Table with Separate Chaining");
        abort();
    }

    if (m > 0)
    {
        /* Allocate memory for the array of slots */
        ht->slots = malloc(m*sizeof(upo_ht_sepchain_slot_t));
        if (ht->slots == NULL)
        {
            perror("Unable to allocate memory for slots of the Hash Table with Separate Chaining");
            abort();
        }

        /* Initialize slots */
        for (i = 0; i < m; ++i)
        {
            ht->slots[i].head = NULL;
        }
    }
    else
    {
        ht->slots = NULL;
    }

    /* Initialize the other fields */
    ht->capacity = m;
    ht->size = 0;
    ht->key_hash = key_hash;
    ht->key_cmp = key_cmp;

    return ht;
}

void upo_ht_sepchain_destroy(upo_ht_sepchain_t ht, int destroy_data)
{
    if (ht != NULL)
    {
        upo_ht_sepchain_clear(ht, destroy_data);
        free(ht->slots);
        free(ht);
    }
}

void upo_ht_sepchain_clear(upo_ht_sepchain_t ht, int destroy_data)
{
    if (ht != NULL && ht->slots != NULL)
    {
        size_t i = 0;

        /* For each slot, clear the associated list of collisions */
        for (i = 0; i < ht->capacity; ++i)
        {
            upo_ht_sepchain_list_node_t *list = NULL;

            list = ht->slots[i].head;
            while (list != NULL)
            {
                upo_ht_sepchain_list_node_t *node = list;

                list = list->next;

                if (destroy_data)
                {
                    free(node->key);
                    free(node->value);
                }

                free(node);
            }
            ht->slots[i].head = NULL;
        }
        ht->size = 0;
    }
}

upo_ht_sepchain_list_node_t * upo_new_list_node_t(void *key, void* value)
{
    upo_ht_sepchain_list_node_t * new = (upo_ht_sepchain_list_node_t *)malloc(sizeof(upo_ht_sepchain_list_node_t)); 

    if (new == NULL)
        perror("unable to allocate memory for upo_new_list_node_t function");
    new -> key = key;
    new -> value = value;
    new -> next = NULL;
    return new;
}

void* upo_ht_sepchain_put(upo_ht_sepchain_t ht, void *key, void *value)
{

    if (ht == NULL || key == NULL || value == NULL)
        return NULL;

    void *old_value = NULL;

    size_t hash_result = ht -> key_hash(key, ht -> capacity);

    upo_ht_sepchain_list_node_t * collision_head = ht -> slots[hash_result].head;
    upo_ht_sepchain_list_node_t * p = collision_head;

    if (collision_head == NULL){
        ht -> slots[hash_result].head = upo_new_list_node_t(key, value);
        ht -> size += 1;
        return old_value;
    }

    while (collision_head != NULL && ht -> key_cmp(collision_head -> key, key) != 0){
        p = collision_head;
        collision_head = collision_head -> next;
    }

    if (collision_head != NULL){
        old_value = collision_head -> value;
        collision_head -> value = value;
    }
    else{
        p-> next = upo_new_list_node_t(key, value);
        old_value = value;
        ht -> size += 1;
    }

    return old_value;
}


void* upo_ht_sepchain_get(const upo_ht_sepchain_t ht, const void *key)
{
    if (ht == NULL || key == NULL)
        return NULL;

    // calculates the hash value and indexes the array
    size_t hash_result = ht -> key_hash(key, ht -> capacity);
    upo_ht_sepchain_list_node_t * collision_head = ((ht -> slots)[hash_result]).head;

    while (collision_head != NULL && ht -> key_cmp(collision_head -> key, key) != 0)
        collision_head = collision_head -> next;

    if (collision_head != NULL)
        return collision_head -> value;
    return NULL;
}
void upo_ht_sepchain_insert(upo_ht_sepchain_t ht, void *key, void *value)
{
    if (ht == NULL || key == NULL || value == NULL)
        return;

    void * searched_key_value = upo_ht_sepchain_get(ht, key);
    if (searched_key_value == NULL)
        upo_ht_sepchain_put(ht, key, value);
}

int upo_ht_sepchain_contains(const upo_ht_sepchain_t ht, const void *key)
{
    if (ht == NULL || key == NULL)
        return 0;
    size_t hash_result = ht -> key_hash(key, ht -> capacity);
    upo_ht_sepchain_list_node_t * collision_head = ((ht -> slots)[hash_result]).head;

    while (collision_head != NULL && ht -> key_cmp(collision_head -> key, key) != 0)
        collision_head = collision_head -> next;
    return collision_head != NULL ? 1: 0;
}

void upo_ht_sepchain_delete(upo_ht_sepchain_t ht, const void *key, int destroy_data)
{

    if (ht == NULL || key == NULL)
        return;
    size_t hash_result = ht -> key_hash(key, ht -> capacity);

    upo_ht_sepchain_list_node_t * collision_head = ((ht -> slots)[hash_result]).head;
    upo_ht_sepchain_list_node_t * p = NULL;

    while (collision_head != NULL && ht -> key_cmp(collision_head -> key, key) != 0)
    {
        p = collision_head;
        collision_head = collision_head -> next;
    }

    if (collision_head != NULL){
        if (p == NULL)
        {
            ((ht -> slots)[hash_result]).head = collision_head -> next;
        }
        else
        {
            p -> next = collision_head -> next;
        }
        if (destroy_data != 0){
            free(collision_head -> key);
            free(collision_head -> value);
        }
        free(collision_head);
        ht -> size -= 1;
    }

}

size_t upo_ht_sepchain_size(const upo_ht_sepchain_t ht)
{
    if (ht != NULL)
        return ht -> size;
    return 0;
}

int upo_ht_sepchain_is_empty(const upo_ht_sepchain_t ht)
{
    return upo_ht_sepchain_size(ht) == 0 ? 1 : 0;
}

size_t upo_ht_sepchain_capacity(const upo_ht_sepchain_t ht)
{
    return (ht != NULL) ? ht->capacity : 0;
}

double upo_ht_sepchain_load_factor(const upo_ht_sepchain_t ht)
{
    return upo_ht_sepchain_size(ht) / (double) upo_ht_sepchain_capacity(ht);
}

upo_ht_comparator_t upo_ht_sepchain_get_comparator(const upo_ht_sepchain_t ht)
{
    return ht->key_cmp;
}

upo_ht_hasher_t upo_ht_sepchain_get_hasher(const upo_ht_sepchain_t ht)
{
    return ht->key_hash;
}


size_t upo_ht_linprob_size(const upo_ht_linprob_t ht)
{
    if (ht == NULL)
        return 0;
    return ht -> size;
}

int upo_ht_linprob_is_empty(const upo_ht_linprob_t ht)
{
    return upo_ht_linprob_size(ht) == 0 ? 1 : 0;
}

size_t upo_ht_linprob_capacity(const upo_ht_linprob_t ht)
{
    return (ht != NULL) ? ht->capacity : 0;
}

double upo_ht_linprob_load_factor(const upo_ht_linprob_t ht)
{
    return upo_ht_linprob_size(ht) / (double) upo_ht_linprob_capacity(ht);
}

upo_ht_linprob_t upo_ht_linprob_create(size_t m, upo_ht_hasher_t key_hash, upo_ht_comparator_t key_cmp)
{
    upo_ht_linprob_t ht = NULL;
    size_t i = 0;

    /* preconditions */
    assert( key_hash != NULL );
    assert( key_cmp != NULL );

    /* Allocate memory for the hash table type */
    ht = malloc(sizeof(struct upo_ht_linprob_s));
    if (ht == NULL)
    {
        perror("Unable to allocate memory for Hash Table with Linear Probing");
        abort();
    }

    /* Allocate memory for the array of slots */
    if (m > 0)
    {
        ht->slots = malloc(m*sizeof(upo_ht_linprob_slot_t));
        if (ht->slots == NULL)
        {
            perror("Unable to allocate memory for slots of the Hash Table with Separate Chaining");
            abort();
        }

        /* Initialize the slots */
        for (i = 0; i < m; ++i)
        {
            ht->slots[i].key = NULL;
            ht->slots[i].value = NULL;
            ht->slots[i].tombstone = 0;
        }
    }
    else
    {
        ht->slots = NULL;
    }

    /* Initialize the other fields */
    ht->capacity = m;
    ht->size = 0;
    ht->key_hash = key_hash;
    ht->key_cmp = key_cmp;

    return ht;
}

void upo_ht_linprob_destroy(upo_ht_linprob_t ht, int destroy_data)
{
    if (ht != NULL)
    {
        upo_ht_linprob_clear(ht, destroy_data);
        free(ht->slots);
        free(ht);
    }
}

void upo_ht_linprob_clear(upo_ht_linprob_t ht, int destroy_data)
{
    if (ht != NULL && ht->slots != NULL)
    {
        size_t i = 0;

        /* For each slot, clear the associated list of collisions */
        for (i = 0; i < ht->capacity; ++i)
        {
            if (ht->slots[i].key != NULL)
            {
                if (destroy_data)
                {
                    free(ht->slots[i].key);
                    free(ht->slots[i].value);
                }
                ht->slots[i].key = NULL;
                ht->slots[i].value = NULL;
                ht->slots[i].tombstone = 0;
            }
        }
        ht->size = 0;
    }
}

void* upo_ht_linprob_put(upo_ht_linprob_t ht, void *key, void *value)
{
    void *old_value = NULL;

    if (ht == NULL || key == NULL || value == NULL)
        return NULL;

    if (upo_ht_linprob_load_factor(ht) >= 0.5)
        upo_ht_linprob_resize(ht, ht -> capacity * 2);

    size_t i = 0;
    size_t ht_capacity = ht -> capacity;
    size_t hash = ht -> key_hash(key, ht_capacity);
    size_t hash_tomb = hash;
    int found_tomb = 0;

    while ( (ht -> slots[hash].key != NULL && ht -> key_cmp(ht -> slots[hash].key, key) != 0) || (ht -> slots[hash].tombstone == 1) )
    {
        if (ht -> slots[hash].tombstone == 1 && found_tomb == 0)
        {
            found_tomb = 1;
            hash_tomb = hash;
        }
        hash = (ht -> key_hash(key, ht_capacity) + (++i)) % ht_capacity;
    }

    if (ht -> slots[hash].key == NULL){
        if (found_tomb == 1)
            hash = hash_tomb;
        ht -> slots[hash].key = key;
        ht -> slots[hash].value = value;
        ht -> slots[hash].tombstone = 0;
        ht -> size += 1;
    }
    else
    {
        old_value = ht -> slots[hash].value;
        ht -> slots[hash].value = value;
    }
    return old_value;
}

void* upo_ht_linprob_get(const upo_ht_linprob_t ht, const void *key)
{
    if (ht == NULL || key == NULL)
        return NULL;

    size_t i = 0;
    size_t capacity = ht -> capacity;
    size_t hash = ht -> key_hash(key, capacity);

    while ((ht -> slots[hash].key != NULL && ht -> key_cmp(ht -> slots[hash].key, key) != 0) || (ht -> slots[hash].tombstone == 1) )
        hash = (ht -> key_hash(key, capacity) + (++i)) % capacity;
    return ht -> slots[hash].value;
}

int upo_ht_linprob_contains(const upo_ht_linprob_t ht, const void *key)
{
    return upo_ht_linprob_get(ht, key) != NULL;
}

void upo_ht_linprob_insert(upo_ht_linprob_t ht, void *key, void *value)
{
    if (ht == NULL || key == NULL || value == NULL)
        return;
    if (upo_ht_linprob_contains(ht, key))
        return;
    upo_ht_linprob_put(ht, key, value);
}


void upo_ht_linprob_delete(upo_ht_linprob_t ht, const void *key, int destroy_data)
{
    if (ht == NULL || key == NULL)
        return;
    size_t i = 0;
    size_t capacity = ht -> capacity;
    size_t hash = ht -> key_hash(key, capacity);
    while ((ht -> slots[hash].key != NULL && ht -> key_cmp(ht -> slots[hash].key, key) != 0) || ht -> slots[hash].tombstone == 1)
        hash = (ht -> key_hash(key, capacity) + (++i)) % capacity;
    if (ht -> slots[hash].key != NULL){
        if (destroy_data != 0)
        {
            free(ht -> slots[hash].key);
            free(ht -> slots[hash].value);
        }
        ht -> slots[hash].key = NULL;
        ht -> slots[hash].value = NULL;
        ht -> slots[hash].tombstone = 1;
        ht -> size -= 1;
        if (upo_ht_linprob_load_factor(ht) <= 0.125)
            upo_ht_linprob_resize(ht, ht -> capacity / 2);
    }
}

void upo_ht_linprob_resize(upo_ht_linprob_t ht, size_t n)
{
    /* preconditions */
    assert( n > 0 );

    if (ht != NULL)
    {
        /* The hash table must be rebuilt from scratch since the hash value of
         * keys will be in general different (due to the change in the
         * capacity). */

        size_t i = 0;
        upo_ht_linprob_t new_ht = NULL;

        /* Create a new temporary hash table */
        new_ht = upo_ht_linprob_create(n, ht->key_hash, ht->key_cmp);
        if (new_ht == NULL)
        {
            perror("Unable to allocate memory for slots of the Hash Table with Separate Chaining");
            abort();
        }

        /* Put in the temporary hash table the key-value pairs stored in the
         * hash table to resize.
         * Note: by calling function 'put' we are also rehashing the keys
         * according to the new capacity. */
        for (i = 0; i < ht->capacity; ++i)
        {
            if (ht->slots[i].key != NULL)
            {
                upo_ht_linprob_put(new_ht, ht->slots[i].key, ht->slots[i].value);
            }
        }

        /* Copy the new slots in the old hash table.
         * To do so we use a trick that avoids to loop for each key-value pair:
         * swap the array of slots, the size and the capacity between new and
         * old hash tables.
         * This way the memory that was allocated for ht is moved to new_ht and
         * is deallocated when new_ht is destroyed. */
        upo_swap(&ht->slots, &new_ht->slots, sizeof ht->slots);
        upo_swap(&ht->capacity, &new_ht->capacity, sizeof ht->capacity);
        upo_swap(&ht->size, &new_ht->size, sizeof ht->size);

        /* Destroy temporary hash table */
        upo_ht_linprob_destroy(new_ht, 0);
    }
}


upo_ht_key_list_t upo_ht_sepchain_keys(const upo_ht_sepchain_t ht)
{
    if (ht == NULL)
        return NULL;

    upo_ht_key_list_t append_list = NULL;
    upo_ht_key_list_t tail_list = append_list;

    for (size_t i = 0; i < ht->capacity; ++i)
    {
        upo_ht_sepchain_list_node_t *list = NULL;

        list = ht->slots[i].head;
        while (list != NULL)
        {
            if (tail_list == NULL){
                tail_list = malloc(sizeof(upo_ht_key_list_t));
                if (tail_list == NULL)
                    perror("unable to allocate memory\n");
                tail_list -> key = list -> key;
                tail_list -> next = NULL;
                append_list = tail_list;
            }
            else{
                upo_ht_key_list_t new_node = malloc(sizeof(upo_ht_key_list_t));
                if (new_node == NULL)
                    perror("unable to allocate memory\n");
                new_node -> key = list -> key;
                new_node -> next = NULL;
                tail_list -> next = new_node;
                tail_list = tail_list -> next;
            }
            list = list->next;
        }
    }
    return append_list;
}

void upo_ht_sepchain_traverse(const upo_ht_sepchain_t ht, upo_ht_visitor_t visit, void *visit_context)
{
    if (ht == NULL || visit == NULL || visit_context == NULL)
        return;
    for (size_t i = 0; i < ht->capacity; ++i)
    {
        upo_ht_sepchain_list_node_t *list = NULL;

        list = ht->slots[i].head;
        while (list != NULL)
        {
            visit(list -> key, list-> value, visit_context);
            list = list->next;
        }
    }
}

upo_ht_key_list_t upo_ht_linprob_keys(const upo_ht_linprob_t ht)
{
    if (ht == NULL)
        return NULL;
    upo_ht_key_list_t append_list = NULL;
    upo_ht_key_list_t tail_list = append_list;

    for (size_t i = 0; i < ht->capacity; ++i)
    {
        if (ht -> slots[i].key != NULL){
            if (tail_list == NULL){
                tail_list = malloc(sizeof(upo_ht_key_list_t));
                if (tail_list == NULL)
                    perror("unable to allocate memory\n");
                tail_list -> key = ht -> slots[i].key;
                tail_list -> next = NULL;
                append_list = tail_list;
            }
            else{
                upo_ht_key_list_t new_node = malloc(sizeof(upo_ht_key_list_t));
                if (new_node == NULL)
                    perror("unable to allocate memory\n");
                new_node -> key = ht -> slots[i].key;
                new_node -> next = NULL;
                tail_list -> next = new_node;
                tail_list = tail_list -> next;
            }
        }
    }
    return append_list;
}

void upo_ht_linprob_traverse(const upo_ht_linprob_t ht, upo_ht_visitor_t visit, void *visit_context)
{
    if (ht == NULL)
        return;
    for (size_t i = 0; i < ht->capacity; ++i)
    {
        if (ht -> slots[i].key != NULL)
            visit(ht -> slots[i].key, ht -> slots[i].value, visit_context);
    }
}


/*** BEGIN of HASH FUNCTIONS ***/


size_t upo_ht_hash_int_div(const void *x, size_t m)
{
    /* preconditions */
    assert( x != NULL );
    assert( m > 0 );

    return *((int*) x) % m;
}

size_t upo_ht_hash_int_mult(const void *x, double a, size_t m)
{
    /* preconditions */
    assert( x != NULL );
    assert( a > 0 && a < 1 );
    assert( m > 0 );

    return floor( m * fmod(a * *((int*) x), 1.0) );
}

size_t upo_ht_hash_int_mult_knuth(const void *x, size_t m)
{
    return upo_ht_hash_int_mult(x, 0.5*(sqrt(5)-1), m);
}

size_t upo_ht_hash_str(const void *x, size_t h0, size_t a, size_t m)
{
    const char *s = NULL;
    size_t h = h0; 

    /* preconditions */
    assert( x != NULL );
    assert( m > 0 );
/*
    assert( a < m );
*/
    assert( h0 < m );

    s = *((const char**) x);
    for (; *s; ++s)
    {
        h = (a*h + *s) % m;
    }

    return h;
}

size_t upo_ht_hash_str_djb2(const void *x, size_t m)
{
    return upo_ht_hash_str(x, 5381U, 33U, m);
}

size_t upo_ht_hash_str_djb2a(const void *x, size_t m)
{
    const char *s = NULL;
    size_t h = 5381U; 

    /* preconditions */
    assert( x != NULL );
    assert( m > 0 );

    s = *((const char**) x);
    for (; *s; ++s)
    {
        h = (33U*h ^ *s) % m;
    }

    return h;
}

size_t upo_ht_hash_str_java(const void *x, size_t m)
{
    return upo_ht_hash_str(x, 0U, 31U, m);
}

size_t upo_ht_hash_str_kr2e(const void *x, size_t m)
{
    return upo_ht_hash_str(x, 0U, 31U, m);
}

size_t upo_ht_hash_str_sgistl(const void *x, size_t m)
{
    return upo_ht_hash_str(x, 0U, 5U, m);
}

size_t upo_ht_hash_str_stlport(const void *x, size_t m)
{
    return upo_ht_hash_str(x, 0U, 33U, m);
}

/*** END of HASH FUNCTIONS ***/
