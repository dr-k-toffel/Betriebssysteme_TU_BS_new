#ifndef __AVL_H__
#define __AVL_H__
//------------------------------------------------------------------------//
#include <stdint.h>
#include <stdlib.h>
//------------------------------------------------------------------------//
//forward declaration of internal used nodes
typedef struct avl_node_t avl_node_t;
// typedefed key type (if nothing is specied, the keytype is uint32_t) otherwise BST_KEY_TYPE
#ifndef BST_KEY_TYPE
	typedef uint32_t avl_key_t;
#else
	typedef BST_KEY_TYPE avl_key_t;
#endif
//For a better readability, callback function pointer type is typedefed to callback_t
typedef void (*callback_t)(void * payload, void * args);
//------------------------------------------------------------------------//
//get's data from tree
extern void * avl_get_data(struct avl_node_t *r, avl_key_t key);
//searches for a key, and deletes this node
extern struct avl_node_t * avl_delete_data(struct avl_node_t * n, avl_key_t key, callback_t callback, void* arg);
//puts data into the tree
extern struct avl_node_t * avl_put_data(struct avl_node_t *r, avl_key_t key, void* data);
//iterates through the tree in ascending order of the keys and calls the callback function
extern void preorder_work(struct avl_node_t *r, callback_t callback, void* arg);
//removes all nodes of the tree by using a callback function to delete the payload
extern void clean_up_avl(struct avl_node_t * n, callback_t callback, void *arg);
//------------------------------------------------------------------------//
#endif
