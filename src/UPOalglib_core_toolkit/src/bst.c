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

#include "bst_private.h"
#include <stdio.h>
#include <stdlib.h>


/**** EXERCISE #1 - BEGIN of FUNDAMENTAL OPERATIONS ****/


upo_bst_t upo_bst_create(upo_bst_comparator_t key_cmp)
{
    upo_bst_t tree = malloc(sizeof(struct upo_bst_s));
    if (tree == NULL)
    {
        perror("Unable to create a binary search tree");
        abort();
    }

    tree->root = NULL;
    tree->key_cmp = key_cmp;

    return tree;
}

void upo_bst_destroy(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear(tree, destroy_data);
        free(tree);
    }
}

void upo_bst_clear_impl(upo_bst_node_t *node, int destroy_data)
{
    if (node != NULL)
    {
        upo_bst_clear_impl(node->left, destroy_data);
        upo_bst_clear_impl(node->right, destroy_data);

        if (destroy_data)
        {
            free(node->key);
            free(node->value);
        }

        free(node);
    }
}

void upo_bst_clear(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear_impl(tree->root, destroy_data);
        tree->root = NULL;
    }
}

int upo_bst_node_is_leave(upo_bst_node_t * node)
{
    /*
     * A leave is by a definition a node which has no children.
     * We must also check if the current pointer is pointing to an 
     * uninitialized memory area to avoid segmentation faults.
     */
    return node != NULL && node -> left == NULL && node -> right == NULL;
}

upo_bst_node_t * upo_bst_new_node(void * key, void * value)
{
    /*
     * A new node is allocated, having the key/value given as function 
     * parameters. If an error occurs allocating memory, then an error is thrown.
     */
    upo_bst_node_t * node = (upo_bst_node_t *) malloc(sizeof(upo_bst_node_t));
    if (node == NULL) perror("error allocating memory for new node\n");
    node -> key = key;
    node -> value = value;
    return node;
}


void upo_bst_insert_rec(upo_bst_node_t * node, void *key, void *value, upo_bst_comparator_t key_cmp)
{
    /* We can only insert a new node whether it is a leave (necessarily)
     * Check then the value of the current leave, if our key is > than the current node value
     * it must be inserted at its right, left otherwise.
     */
    int result = key_cmp(key, node -> key);

    if (upo_bst_node_is_leave(node)){
        //leaf here, put the new value in the right place
        if (result < 0) 
            node -> left = upo_bst_new_node(key, value);
        else 
            node -> right = upo_bst_new_node(key, value);
        return;
    }
    else if (result < 0) {
        if (node -> left == NULL) 
            node -> left = upo_bst_new_node(key, value);
        else
            upo_bst_insert_rec(node -> left, key, value, key_cmp);
    }
    else if (node -> right == NULL && result >= 0)
        node -> right = upo_bst_new_node(key, value);
    else
        upo_bst_insert_rec(node -> right, key, value, key_cmp);
}

void upo_bst_insert(upo_bst_t tree, void *key, void *value)
{
    /*
     * If the tree is NULL, nothing is inserted.
     * If the tree is empty, then a new node with the chosen key/value is on top.
     * If it does contain already the value, nothing is done.
     * If it doesn't contain it, then insert it recursevily in the right place.
     */
    if (tree == NULL) return;
    if (upo_bst_is_empty(tree))
        tree -> root = upo_bst_new_node(key, value);
    else if (!upo_bst_contains(tree, key))
        upo_bst_insert_rec(tree -> root, key, value, tree -> key_cmp);
}

upo_bst_node_t * upo_bst_get_node(upo_bst_node_t * node, const void *key, upo_bst_comparator_t key_cmp){
    if (node == NULL) return NULL;
    int result = key_cmp(key, node -> key);
    if (result == 0) return node;
    if (result < 0) return upo_bst_get_node(node -> left, key, key_cmp);
    if (result > 0) return upo_bst_get_node(node -> right, key, key_cmp);
}

void* upo_bst_get(const upo_bst_t tree, const void *key)
{
    if (! upo_bst_is_empty(tree)){
        upo_bst_node_t * node = upo_bst_get_node(tree -> root, key, tree -> key_cmp);
        if (node != NULL) return node -> value;
        else return NULL;
    }
    return NULL;
}

void* upo_bst_put(upo_bst_t tree, void *key, void *value)
    /*
     * If the node doesn't exist, then it is created and inserted.
     * The value of the new node is returned.
     * Otherwise, if it exists, a new value is written in the same node
     * and the old value is returned.
     */
{
    if (tree == NULL) return NULL;
    if (! upo_bst_is_empty(tree) && upo_bst_contains(tree, key)){
        upo_bst_node_t * node = upo_bst_get_node(tree -> root, key, tree -> key_cmp);
        void * old_value = node -> value;
        node -> value = value;
        return old_value;
    } 
    else upo_bst_insert(tree, key, value);
    return value;
}

int upo_bst_contains(const upo_bst_t tree, const void *key)
{
    return upo_bst_get(tree, key) != NULL;
}


void upo_bst_delete(upo_bst_t tree, const void *key, int destroy_data)
{
    /* There are three possible scenarios :
     * 1 - the node to be removed is a leaf, simplest case resolved with the deletion
     * 2 - the node has a child : the node has to be removed and the successor has
     *     to be attached to the current node parent.
     * 3 - the node has two children, in this case we know that we need to choose
     *     the predecessor (which is maximum leftmost child).
     * */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

size_t upo_bst_size_rec(const upo_bst_node_t * node){
    /*
     * If the node is NULL, then return 0.
     * Otherwise it must count as a valide node, trasverse all the tree
     * left to right.
     * The signature of the function assumes the node is const as it won't
     * be changed (we only "read" the values).
     */
    if (node == NULL) return 0;
    return 1 + upo_bst_size_rec(node -> left) + upo_bst_size_rec(node -> right);
}

size_t upo_bst_size(const upo_bst_t tree)
{
    /*
     * The size of a tree consists in the number of nodes/leaves
     * that it contains, so we must count each one to get the correct size.
     * We do this recursively counting each valid node in upo_bst_size_rec
     */
    if (tree == NULL || upo_bst_is_empty(tree))
        return 0;
    return upo_bst_size_rec(tree -> root);
}

size_t upo_max_height(size_t height, size_t other)
{
    /*
     * This function returns the max height between
     * two values.
     */
    return height >= other ? height : other;
}

size_t upo_bst_height_rec(upo_bst_node_t * node)
{
    /*
     * If it is a leaf or null reference, then 0 is returned (because
     * it is not affecting the height of the tree).
     * Otherwise get the max height between the left node and the right node,
     * because the height of a tree is by definition the max number of edges between
     * the root and the farthest leaf.
     */
    if (node == NULL || upo_bst_node_is_leave(node))
        return 0;
    else
        return 1 + upo_max_height(upo_bst_height_rec(node -> left), upo_bst_height_rec(node -> right));
}

size_t upo_bst_height(const upo_bst_t tree)
{
    /*
     * Returns the height of the current tree.
     */
    if (tree == NULL || upo_bst_is_empty(tree))
        return 0;
    else upo_bst_height_rec(tree -> root);
}

void upo_bst_traverse_in_order(const upo_bst_t tree, upo_bst_visitor_t visit, void *visit_context)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

int upo_bst_is_empty(const upo_bst_t tree)
{
    return tree == NULL || tree -> root == NULL;
}


/**** EXERCISE #1 - END of FUNDAMENTAL OPERATIONS ****/


/**** EXERCISE #2 - BEGIN of EXTRA OPERATIONS ****/


void* upo_bst_min(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void* upo_bst_max(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void upo_bst_delete_min(upo_bst_t tree, int destroy_data)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void upo_bst_delete_max(upo_bst_t tree, int destroy_data)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void* upo_bst_floor(const upo_bst_t tree, const void *key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void* upo_bst_ceiling(const upo_bst_t tree, const void *key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

upo_bst_key_list_t upo_bst_keys_range(const upo_bst_t tree, const void *low_key, const void *high_key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

upo_bst_key_list_t upo_bst_keys(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

int upo_bst_is_bst(const upo_bst_t tree, const void *min_key, const void *max_key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}


/**** EXERCISE #2 - END of EXTRA OPERATIONS ****/


upo_bst_comparator_t upo_bst_get_comparator(const upo_bst_t tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    return tree->key_cmp;
}
