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

#include "stack_private.h"
#include <stdio.h>
#include <stdlib.h>

upo_stack_node_t* upo_stack_node_create(void *data)
{
    upo_stack_node_t *node = malloc(sizeof(upo_stack_node_t));
    if (node == NULL)
    {
        perror("Unable to create a node stack");
        abort();
    }

    node->data = data;
    node->next = NULL;

    return node;
}

upo_stack_t upo_stack_create()
{
    upo_stack_t stack = malloc(sizeof(struct upo_stack_s));
    if (stack == NULL)
    {
        perror("Unable to create a stack");
        abort();
    }

    stack->top = NULL;
    stack->size = 0;

    return stack;
}

void upo_stack_destroy(upo_stack_t stack, int destroy_data)
{
    if (stack != NULL)
    {
        upo_stack_clear(stack, destroy_data);
        free(stack);
    }
}

void upo_stack_push(upo_stack_t stack, void *data)
{
    /* TO STUDENTS:
     * se non presente sostituisco puntatore a null con il primo elemento
     * altrimenti alloco memoria per un nuovo nodo che ha come next il nodo 
     * puntato attualmente dallo stack e aggiorno poi i riferimenti dello 
     * stack stesso 
     * aggiorno top con lo stesso reference
     * aumento il numero di elementi dello stack stesso
     *
     *  
     *  Remove the following two lines and put here your implementation. */
    if (stack != NULL) {
        upo_stack_node_t * new_node = upo_stack_node_create(data);
        new_node -> next = stack -> top;
        stack -> top = new_node;
        stack -> size++;
    }
}

void upo_stack_pop(upo_stack_t stack, int destroy_data)
{
    if (!upo_stack_is_empty(stack)){

    upo_stack_node_t * node = stack -> top;
    stack -> top = node -> next;

    if (destroy_data != 0)
        free(node -> data);
    free(node);
    stack -> size--;
    }
}

void* upo_stack_top(const upo_stack_t stack)
{
    return !upo_stack_is_empty(stack) ?  stack -> top -> data : NULL;
}

int upo_stack_is_empty(const upo_stack_t stack)
{
    return stack != NULL && stack -> size != 0 ? 0 : 1;
}

size_t upo_stack_size(const upo_stack_t stack)
{
    return !upo_stack_is_empty(stack) ? stack -> size : 0;
}

void upo_stack_clear(upo_stack_t stack, int destroy_data)
{
    while (!upo_stack_is_empty(stack))
        upo_stack_pop(stack, destroy_data);
}
