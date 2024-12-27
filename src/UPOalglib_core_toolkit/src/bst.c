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

int upo_bst_node_is_leaf(upo_bst_node_t * node)
{
    /*
     * A leave is by a definition a node which has no children.
     * We must also check if the current pointer is pointing to an 
     * uninitialized memory area to avoid segmentation faults.
     */
    return node != NULL && node -> left == NULL && node -> right == NULL;
}

upo_bst_node_t * upo_bst_new_node(void* key, void* value)
{
    /*
     * A new node is allocated, having the key/value given as function 
     * parameters. If an error occurs allocating memory, then an error is thrown.
     */
    upo_bst_node_t * node = (upo_bst_node_t *) malloc(sizeof(upo_bst_node_t));
    if (node == NULL)
        perror("error allocating memory for new node\n");
    node -> key = key;
    node -> value = value;
    node -> left = NULL;
    node -> right = NULL;
    return node;
}


upo_bst_node_t * upo_bst_insert_rec(upo_bst_node_t * node, void *key, void *value, upo_bst_comparator_t key_cmp)
{
    /* We can only insert a new node whether it is a leave (necessarily)
     * Check then the value of the current leave, if our key is > than the current node value
     * it must be inserted at its right, left otherwise.
     */
    if (node == NULL)
        return upo_bst_new_node(key, value);

    int result = key_cmp(key, node -> key);
    if (result < 0)
        node -> left = upo_bst_insert_rec(node -> left, key, value, key_cmp);
    else if (result > 0) 
        node -> right = upo_bst_insert_rec(node -> right, key, value, key_cmp);
    return node;
}

void upo_bst_insert(upo_bst_t tree, void *key, void *value)
{
    /*
     * If the tree is NULL, nothing is inserted.
     * If the tree is empty, then a new node with the chosen key/value is on top.
     * If it does contain already the value, nothing is done.
     * If it doesn't contain it, then insert it recursevily in the right place.
     */
    if (tree == NULL || key == NULL) return;
    tree -> root = upo_bst_insert_rec(tree -> root, key, value, tree -> key_cmp);
}

upo_bst_node_t * upo_bst_get_node(upo_bst_node_t * node, const void *key, upo_bst_comparator_t key_cmp){
    /*
     * This function returns a node reference, having the key indicated as parameter.
     * If not present, a NULL reference is returned.
     */
    if (node == NULL) return NULL;
    int result = key_cmp(key, node -> key);
    if (result == 0) return node;
    if (result < 0)
        return upo_bst_get_node(node -> left, key, key_cmp);
    else return upo_bst_get_node(node -> right, key, key_cmp);
}

void* upo_bst_get(const upo_bst_t tree, const void *key)
    /*
     * This function gets the key value indicated in the parameter.
     * If it doesn't, then a NULL reference is returned.
     */
{
    upo_bst_node_t * node = upo_bst_get_node(tree -> root, key, tree -> key_cmp);
    if (node != NULL) 
        return node -> value;
    else 
        return NULL;
}

void* upo_bst_put_rec(upo_bst_node_t * node, void *key, void *value, void *old_value, upo_bst_comparator_t key_cmp)
{
    old_value = NULL;

    if (node == NULL)
        return upo_bst_new_node(key, value);
    int result = key_cmp(key, node -> key);

    if (result < 0)
        node -> left = upo_bst_put_rec(node -> left, key, value, old_value, key_cmp);
    else if (result > 0)
        node -> right = upo_bst_put_rec(node -> right, key, value, old_value, key_cmp);
    else {
        old_value = node -> value;
        node -> value = value;
    }
    return node;
}

void* upo_bst_put(upo_bst_t tree, void *key, void *value)
    /*
     * If the node doesn't exist, then it is created and inserted.
     * The value of the new node is returned.
     * Otherwise, if it exists, a new value is written in the same node
     * and the old value is returned.
     */
{
    void * old_value = NULL;
    if (tree == NULL)
        return NULL;
    tree -> root = upo_bst_put_rec(tree -> root, key, value, old_value, tree -> key_cmp);
    return old_value;
}

int upo_bst_contains(const upo_bst_t tree, const void *key)
{
    /*
     * This function indicates whether a tree contains a given key or not.  
     */
    if (tree == NULL || key == NULL)
        return 0;
    return upo_bst_get_node(tree -> root, key, tree -> key_cmp) != NULL;
}

upo_bst_node_t * upo_bst_max_node(upo_bst_node_t * node)
{
    /*
     * This function returns the max right node from a given 
     * node, which is by definition the highest value in a tree.
     * It searches through the right side until it gets a null
     * reference as next node.
     */
    if (node -> right == NULL)
        return node -> key;
    else
        upo_bst_max_node(node -> right);
}

upo_bst_node_t * upo_bst_predecessor(upo_bst_node_t * node)
    /*
     * By the algorithmic definition we know that the predecessor
     * is the righmost node of the left tree of the considered node.
     * I assume that the current node has both children.
     */
{
    if (node -> left != NULL)
        return upo_bst_max_node(node -> left);
    return NULL;
}

void upo_bst_destroy_node(upo_bst_node_t ** node, int destroy_data){
    /*
     * This function frees the node, optionally it will free
     * the related key/value pointers when the destroy_data parameter
     * is not 0.
     */
    if (destroy_data != 0){
        free((*node) -> key);
        free((*node) -> value);
    }
    free(*node);
    *node = NULL;
}
void upo_bst_node_copy(upo_bst_node_t * dst, upo_bst_node_t * src){
    /*
     * Copies the key/value of a source node to the destination node
     */
    if (dst == NULL || src == NULL)
        return;
    dst -> key = src -> key;
    dst -> value = src -> value;
}

upo_bst_node_t * upo_bst_delete_rec(upo_bst_node_t * node, const void *key, int destroy_data, upo_bst_comparator_t key_cmp){
    /*
     * There are three cases :
     * 1) the node is null
     * 2) the key is less than the current key, so we must go left in the tree
     * 3) the key is bigger than the current key, so we must go right in the tree
     * 4) the current node is the key we were looking for and it is a leaf, so just delete it!
     * 5) the current node is the key we were looking for but it has two children:
     * find the predecessor (maximum of the left side of the tree) and replace it
     */

    if (node == NULL)
        return NULL;
    int result = key_cmp(key, node -> key);

    if (result < 0)
        node -> left = upo_bst_delete_rec(node -> left, key, destroy_data, key_cmp);

    else if (result > 0)
        node -> right = upo_bst_delete_rec(node -> right, key, destroy_data, key_cmp);

    else if (node -> left != NULL && node -> right != NULL)
        {
            upo_bst_node_t * predecessor = upo_bst_predecessor(node);
            upo_bst_node_copy(node, predecessor); 
            node -> left = upo_bst_delete_rec(node -> left, predecessor -> key, destroy_data, key_cmp);
        }
    else {
        upo_bst_node_t * tmp = node;
        if (node -> right != NULL)
            node = node -> right;
        else
            node = node -> left;
        upo_bst_destroy_node(&tmp, destroy_data);
    }
    return node;
}


void upo_bst_delete(upo_bst_t tree, const void *key, int destroy_data)
{
    /* If the tree is null or empty or it doesn't contain the given key, we shouldn't
     * try to delete the key as absent.
     * */
    if (!upo_bst_contains(tree, key))
        return;
    else tree -> root = upo_bst_delete_rec(tree -> root, key, destroy_data, tree -> key_cmp);
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
    if (upo_bst_is_empty(tree))
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
    if (node == NULL || upo_bst_node_is_leaf(node))
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

void upo_bst_traverse_in_order_rec(upo_bst_node_t * node, upo_bst_visitor_t visit, void *visit_context)
{
    /*
     * Visit the tree in order.
     * If the current node is a leaf then return, in the other case
     * we can visit the left node and the right node.
     */
    if (node == NULL) return;
    upo_bst_traverse_in_order_rec(node -> left, visit, visit_context);
    visit(node -> key, node -> value, visit_context);
    upo_bst_traverse_in_order_rec(node -> right, visit, visit_context);
}

void upo_bst_traverse_in_order(const upo_bst_t tree, upo_bst_visitor_t visit, void *visit_context)
{
    /*
     * If the tree is NULL or empty, then return.
     * Otherwise visit the tree starting from the root.
     */
    if (tree == NULL || upo_bst_is_empty(tree))
        return;
    upo_bst_traverse_in_order_rec(tree -> root, visit, visit_context);
}

int upo_bst_is_empty(const upo_bst_t tree)
{
    return tree == NULL || tree -> root == NULL;
}


/**** EXERCISE #1 - END of FUNDAMENTAL OPERATIONS ****/


/**** EXERCISE #2 - BEGIN of EXTRA OPERATIONS ****/

void * upo_bst_min_rec(upo_bst_node_t * node)
{
    if (node -> left == NULL)
        return node -> key;
    else
        return upo_bst_min_rec(node -> left);
}

void* upo_bst_min(const upo_bst_t tree)
    /*
     * If the tree is empty or NULL then a NULL is returned.
     * Otherwise the leftmost leaf key is returned.
     */
{
    if (upo_bst_is_empty(tree))
        return NULL;
    return upo_bst_min_rec(tree -> root);
}

void* upo_bst_max(const upo_bst_t tree)
    /*
     * If the tree is empty or NULL then a NULL is returned.
     * Otherwise the rightmost leaf key is returned.
     */
{
    if (upo_bst_is_empty(tree))
        return NULL;
    return upo_bst_max_node(tree -> root);
}

void upo_bst_delete_min(upo_bst_t tree, int destroy_data)
    /*
     * This function deletes the minimum leaf of the tree,
     * if present.
     */
{
    if (upo_bst_is_empty(tree))
        return;
    void * min_node_key = upo_bst_min(tree);
    if (min_node_key != NULL){
        upo_bst_node_t * min_node = upo_bst_get_node(tree -> root, min_node_key, tree -> key_cmp);
        if (min_node != NULL)
            upo_bst_delete(tree, min_node -> key, destroy_data);
    }
}

void upo_bst_delete_max(upo_bst_t tree, int destroy_data)
    /*
     * This function deletes the maximum leaf of the tree,
     * if present.
     */
{
    if (upo_bst_is_empty(tree))
        return;
    void * max_node_key = upo_bst_max(tree);
    if (max_node_key != NULL){
        upo_bst_node_t * max_node = upo_bst_get_node(tree -> root, max_node_key, tree -> key_cmp);
        if (max_node != NULL)
            upo_bst_delete(tree, max_node -> key, destroy_data);
    }
}

void * upo_bst_floor_rec(upo_bst_node_t * node, const void * key, upo_bst_comparator_t key_cmp){

    if (node == NULL)
        return NULL;

    int cmp_result = key_cmp(node -> key, key);

    if (cmp_result == 0)
        return node -> key;
    if (cmp_result < 0)
    {
        void * right_res = upo_bst_floor_rec(node -> right, key, key_cmp);
        return right_res ? right_res : node -> key;
    }
    else
        return upo_bst_floor_rec(node -> left, key, key_cmp); 
}

void* upo_bst_floor(const upo_bst_t tree, const void *key)
{
    if (upo_bst_is_empty(tree) || key == NULL)
        return NULL;
    if (upo_bst_contains(tree, key)){
        return (upo_bst_get_node(tree -> root, key, tree -> key_cmp)) -> key;
    }
    void * min = upo_bst_min(tree);
    void * max = upo_bst_max(tree);

    if (tree -> key_cmp(key, min) < 0)
        return NULL;
    if (tree -> key_cmp(key, max) > 0)
        return max;
    else return upo_bst_floor_rec(tree -> root, key, tree -> key_cmp);
}

void * upo_bst_ceiling_rec(upo_bst_node_t * node, const void * key, upo_bst_comparator_t key_cmp){

    if (node == NULL)
        return NULL;

    int cmp_result = key_cmp(node -> key, key);

    if (cmp_result == 0)
        return node -> key;

    if (cmp_result > 0){
        void * left_value = upo_bst_ceiling_rec(node -> left, key, key_cmp);
        return left_value ? left_value : node -> key;
    }
    else return upo_bst_ceiling_rec(node -> right, key, key_cmp);
}

void* upo_bst_ceiling(const upo_bst_t tree, const void *key)
{
    /*
     * The ceiling function retrieves the smallest key in the
     * tree that is > than the current given input key.
     * If it is contained, than the key is returned.
     */
    if (upo_bst_is_empty(tree) || key == NULL)
        return NULL;

    if (upo_bst_contains(tree, key)){
        return (upo_bst_get_node(tree -> root, key, tree -> key_cmp)) -> key;
    }

    void * min = upo_bst_min(tree);
    void * max = upo_bst_max(tree);

    if (tree -> key_cmp(key, min) < 0)
        return min;
    if (tree -> key_cmp(key, max) > 0)
        return NULL;

    else return upo_bst_ceiling_rec(tree -> root, key, tree -> key_cmp);
}

upo_bst_key_list_t upo_bst_initialize_list() {
    /*
     * Utility function to create a new node for the list
     */
    upo_bst_key_list_t keys_list = (upo_bst_key_list_t) malloc(sizeof(*keys_list));
    if (keys_list == NULL)
        perror("\nerror allocating memory for keys_list\n");
    keys_list -> next = NULL;
    keys_list -> key = NULL;
    return keys_list;
}

void upo_find_keys_tail(upo_bst_key_list_t * tail){
    if (*tail == NULL)
        return;
    while ((*tail) -> next != NULL)
        *tail = (*tail) -> next;
}

void upo_bst_keys_range_rec(upo_bst_node_t * node, const void *low_key, const void *high_key, upo_bst_comparator_t key_cmp, upo_bst_key_list_t keys_list){

    if (node == NULL)
        return;

    upo_bst_keys_range_rec(node -> left, low_key, high_key, key_cmp, keys_list);

    if (key_cmp(node -> key, low_key) >= 0 && key_cmp(node -> key, high_key) <= 0){

        upo_bst_key_list_t tail = keys_list;
        while (tail -> next != NULL)
            tail = tail -> next;
        tail -> key = node -> key;
        tail -> next = upo_bst_initialize_list();
    }
    upo_bst_keys_range_rec(node -> right, low_key, high_key, key_cmp, keys_list);
}

upo_bst_key_list_t upo_bst_keys_range(const upo_bst_t tree, const void *low_key, const void *high_key)
{
    if (upo_bst_is_empty(tree))
        return NULL;
    upo_bst_key_list_t keys_list = upo_bst_initialize_list();
    upo_bst_keys_range_rec(tree -> root, low_key, high_key, tree -> key_cmp, keys_list);
    return keys_list;
}


void upo_bst_keys_rec(upo_bst_node_t * node, upo_bst_key_list_t keys_list){
    /*
     * base case: leaf here
     * Visit in pre-order
     */
    if (node == NULL)
        return;

    upo_bst_keys_rec(node -> left, keys_list);

    upo_bst_key_list_t tail = keys_list;
    while (tail -> next != NULL)
        tail = tail -> next;
    tail -> key = node -> key;
    tail -> next = upo_bst_initialize_list();

    upo_bst_keys_rec(node -> right, keys_list);
}

upo_bst_key_list_t upo_bst_keys(const upo_bst_t tree)
    /*
     * This function retrieves all the keys from a binary search tree
     * and puts them in a linked list.
     */
{
    if (upo_bst_is_empty(tree))
        return NULL;
    upo_bst_key_list_t keys_list = upo_bst_initialize_list();
    upo_bst_keys_rec(tree -> root, keys_list);
    return keys_list;
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
